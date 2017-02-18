#pragma once

#include <list>
#include <queue>
#include <mutex>
#include <atomic>
#include <future>
#include <condition_variable>

#include "task.hpp"
#include "thread.hpp"

namespace threading {

	class ThreadPool {
	private:
		template <typename T>
		struct PromisedFunction {
		public:
			PromisedFunction(std::promise<T> p, std::function<T()> f)
				: Promise(p), Function(f) { }
			std::promise<T> Promise;
			std::function<T()> Function;
		};

	public:
		class ThreadPoolBuilder;

		template <typename TReturn>
		auto Submit(std::function<TReturn()>&& function) -> std::future<decltype(function())> {
			if (m_exit) {
				// Todo: Throw specific exception type
				throw std::exception();
			}

			PromisedFunction<TReturn>* pf = new PromisedFunction<TReturn>;
			pf->Promise = std::promise<TReturn>();
			pf->Function = function;

			std::shared_ptr<PromisedFunction<TReturn>> data = std::make_shared(std::promise<TReturn>(), std::move(function));

			std::future<TReturn> future = data->Promise.get_future();

			{
				std::lock_guard<std::mutex> lg(m_taskLock);
				m_taskQueue.emplace([data]() {
					try {
						data->Promise.set_value(data->Function());
					}
					catch (...) {
						data->Promise.set_exception(std::current_exception());
					}
				});
			}

			m_signal.notify_one();
			return std::move(future);

		}

		unsigned int ThreadCount();

		void AddThreads(unsigned int numNewThreads = -1);

		void ReleaseThreads(unsigned int numThreadsToKill);

	private:
		ThreadPool(unsigned int numThreads);

		void Do();

		unsigned int m_numThreads;

		std::list<std::thread> m_threads;

		std::queue<Task> m_taskQueue;

		std::mutex m_taskLock;

		std::condition_variable m_signal;

		std::atomic<bool> m_exit = false;

		std::atomic<bool> m_stopWorking = false;

		friend class ThreadPoolBuilder;
	};

	class ThreadPool::ThreadPoolBuilder {
	public:
		ThreadPoolBuilder();

		ThreadPoolBuilder& WithNumThreads(unsigned int threadCount);

		ThreadPool Build();

	private:
		static const constexpr unsigned int m_defaultThreadCount = 1;

	};

}