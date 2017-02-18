#pragma once

#include <list>
#include <deque>
#include <mutex>
#include <atomic>
#include <future>
#include <memory>
#include <condition_variable>

namespace threading {

	class ThreadPool {
	private:
		template <typename T>
		struct PromisedFunction {
		public:
			PromisedFunction<T>(std::promise<T> p, std::function<T()> f)
				: Promise(std::move(p)), Function(std::move(f)) { }
			std::promise<T> Promise;
			std::function<T()> Function;
		};

	public:
		class ThreadPoolBuilder;

		~ThreadPool();

		void Abort();

		void Stop();

		void StopOnceComplete();

		template <typename TReturn>
		auto Submit(std::function<TReturn()>&& function) -> std::future<decltype(function())> {
			if (m_exit) {
				// Todo: Throw specific exception type
				throw std::exception();
			}

			std::shared_ptr<PromisedFunction<TReturn>> data = std::shared_ptr<PromisedFunction<TReturn>>(new PromisedFunction<TReturn>(std::promise<TReturn>(), std::move(function)));

			std::future<TReturn> future = data->Promise.get_future();

			{
				std::lock_guard<std::mutex> lg(m_taskLock);
				m_taskQueue.emplace_back([data]() {
					try {
						ExecuteAndSetData<TReturn>(data);
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

		void AddThreads(unsigned int numNewThreads = 0);

	private:
		ThreadPool(unsigned int numThreads);

		void Do();

		void JoinAllThreads();

		template <typename TReturn>
		static inline void ExecuteAndSetData(const std::shared_ptr<PromisedFunction<TReturn>>& data) {
			data->Promise.set_value(data->Function());
		}

		template<>
		static inline void ExecuteAndSetData<void>(const std::shared_ptr<PromisedFunction<void>>& data) {
			data->Function();
			data->Promise.set_value();
		}

		unsigned int m_numThreads;

		std::deque<std::thread> m_threads;

		std::deque<std::function<void()>> m_taskQueue;

		std::mutex m_taskLock;

		std::condition_variable m_signal;

		std::atomic<bool> m_exit = false;

		std::atomic<bool> m_stopWorking = false;

		void operator=(const ThreadPool&) = delete;

		ThreadPool(const ThreadPool&) = delete;

		friend class ThreadPoolBuilder;
	};

	class ThreadPool::ThreadPoolBuilder {
	public:
		ThreadPoolBuilder();

		ThreadPoolBuilder& WithNumThreads(unsigned int threadCount);

		std::unique_ptr<ThreadPool> Build();

	private:
		unsigned int m_threadCount;

		static const constexpr unsigned int s_defaultThreadCount = 1;

	};

}