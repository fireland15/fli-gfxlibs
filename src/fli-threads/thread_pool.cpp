#include "thread_pool.hpp"

namespace threading {

	ThreadPool::ThreadPool(unsigned int numThreads) {
		if (numThreads < 1) {
			numThreads = std::thread::hardware_concurrency() + 1;
		}
		while (numThreads--) {
			m_threads.push_back(std::thread(&ThreadPool::Do, this));
		}
	}

	ThreadPool::~ThreadPool() {
		Abort();
	}

	void ThreadPool::Abort() {
		m_exit = true;
		m_stopWorking = true;
		m_signal.notify_all();
		JoinAllThreads();

		{
			std::lock_guard<std::mutex> lg(m_taskLock);
			m_taskQueue.clear();
		}
	}

	void ThreadPool::Stop() {
		m_exit = true;
		m_stopWorking = true;
		m_signal.notify_all();
	}

	void ThreadPool::StopOnceComplete() {
		Stop();
		JoinAllThreads();
		if (!m_taskQueue.empty()) {
			throw std::exception("Error");
		}
	}

	void ThreadPool::Do() {
		std::unique_lock<std::mutex> ul(m_taskLock);
		while (!m_exit || (!m_stopWorking && !m_taskQueue.empty())) {
			if (!m_taskQueue.empty()) {
				std::function<void()> work(std::move(m_taskQueue.front()));
				m_taskQueue.pop_front();
				ul.unlock();
				work();
				ul.lock();
			}
			else {
				m_signal.wait(ul);
			}
		}
	}

	void ThreadPool::JoinAllThreads() {
		for (auto& thread : m_threads) {
			thread.join();
		}

		m_threads.clear();
	}

	unsigned int ThreadPool::ThreadCount() {
		return (unsigned int)m_threads.size();
	}

	void ThreadPool::AddThreads(unsigned int numNewThreads) {
		while (numNewThreads--) {
			m_threads.push_back(std::thread(&ThreadPool::Do, this));
		}
	}

	ThreadPool::ThreadPoolBuilder::ThreadPoolBuilder() {
		m_threadCount = s_defaultThreadCount;
	}

	ThreadPool::ThreadPoolBuilder& ThreadPool::ThreadPoolBuilder::WithNumThreads(unsigned int threadCount) {
		if (threadCount <= 0) {
			threadCount = 1;
		}

		m_threadCount = threadCount;

		return *this;
	}

	std::unique_ptr<ThreadPool> ThreadPool::ThreadPoolBuilder::Build() {
		unsigned int threadCount = m_threadCount;
		m_threadCount = s_defaultThreadCount;

		return std::unique_ptr<ThreadPool>(new ThreadPool(threadCount));
	}

}