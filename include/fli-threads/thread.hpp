#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

#include "task.hpp"

namespace threading {

	class Thread {
	public:
		class ThreadInitializationData {
		public:
			std::queue<Task>* TaskQueue;
			std::mutex* TaskQueueLock;
			std::condition_variable* TaskQueueNotEmpty;
			std::condition_variable* TaskQueueNotFull;
			bool* ShouldDie = false;
		};

		Thread();

	private:
		static Task GetNextTask(std::mutex* m, std::condition_variable* cv_wait, std::condition_variable* cv_notify, std::queue<Task>* queue) {
			std::unique_lock<std::mutex> l(*m);

			cv_wait->wait(l, [queue]() { return !queue->empty(); });

			Task t = queue->front();
			queue->pop();

			cv_notify->notify_one();

			return t;
		}

		static void ThreadMain(ThreadInitializationData* initData) {
			std::queue<Task>* taskQueue = initData->TaskQueue;
			std::mutex* lock = initData->TaskQueueLock;
			std::condition_variable* notFull = initData->TaskQueueNotFull;
			std::condition_variable* notEmpty = initData->TaskQueueNotEmpty;
			bool* shouldDie = initData->ShouldDie;

			while (!*(shouldDie)) {
				Task t = GetNextTask(lock, notFull, notEmpty, taskQueue);

				t.Execute();
			}
		}

	};

}