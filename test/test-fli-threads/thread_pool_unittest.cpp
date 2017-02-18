#include <fli-threads\thread_pool.hpp>
#include <gtest\gtest.h>

namespace {

	using namespace threading;

	int CreateNumber() {
		return 42;
	}

	TEST(ThreadPoolUnitTest, Submit) {
		ThreadPool::ThreadPoolBuilder builder;
		builder.WithNumThreads(3);
		auto pool = builder.Build();

		std::future<int> f1 = pool->Submit(std::function<int()>(&CreateNumber));
		std::future<int> f2 = pool->Submit<int>([]() { 
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
			return 34;
		});

		f1.wait();
		f2.wait();

		pool->StopOnceComplete();
	}

	TEST(ThreadPoolUnitTest, AddThreads) {
		ThreadPool::ThreadPoolBuilder builder;
		builder.WithNumThreads(3);
		auto pool = builder.Build();

		EXPECT_EQ(3, pool->ThreadCount());

		pool->AddThreads(3);

		EXPECT_EQ(6, pool->ThreadCount());

		pool->StopOnceComplete();
	}

	TEST(ThreadPoolBuilderUnitTest, DefaultNumberOfThreads) {
		ThreadPool::ThreadPoolBuilder builder;
		auto pool = builder.Build();

		EXPECT_EQ(1, pool->ThreadCount());

		pool->StopOnceComplete();
	}

	TEST(ThreadPoolBuilderUnitTest, MultipleThreads) {
		ThreadPool::ThreadPoolBuilder builder;
		builder.WithNumThreads(45);
		auto pool = builder.Build();

		EXPECT_EQ(45, pool->ThreadCount());

		pool->StopOnceComplete();
	}

}