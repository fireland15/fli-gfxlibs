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

	void ThreadPool::Do() {
		std::unique_lock<std::mutex> ul(m_taskLock);
		while (!m_exit || (!m_stopWorking && !m_taskQueue.empty())) {
			if (!m_taskQueue.empty()) {

			}
		}
	}

	unsigned int ThreadPool::ThreadCount() {
		return (unsigned int)m_threads.size();
	}

	void ThreadPool::AddThreads(unsigned int numNewThreads) {
		throw std::exception("Attempted to add more threads to pool, but functionality is disabled.");
	}

	void ThreadPool::ReleaseThreads(unsigned int numThreadsToKill) {
		throw std::exception("Attempted to remove threads frompool, but functionality is disabled.");
	}

	ThreadPool::ThreadPoolBuilder::ThreadPoolBuilder() {

	}

	ThreadPool::ThreadPoolBuilder& ThreadPool::ThreadPoolBuilder::WithNumThreads(unsigned int threadCount) {

	}

	ThreadPool ThreadPool::ThreadPoolBuilder::Build() {

	}

}