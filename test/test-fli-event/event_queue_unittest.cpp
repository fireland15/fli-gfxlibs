#include <functional>

#include <gtest\gtest.h>
#include <fli-event\event_queue.hpp>
#include <fli-event\event_handler.hpp>

namespace {

	using namespace events;

	TEST(EventQueueUnitTest, ConnectHandler) {
		EventHandler<int> handler([](int e) { /* NO-OP */ });

		EventQueue<int> queue;
		EXPECT_EQ(0, queue.connected_count());

		queue.connect(&handler);

		EXPECT_EQ(1, queue.connected_count());
	}

	TEST(EventQueueUnitTest, ConnectIHandler) {
		IEventHandler* handler = new EventHandler<int>([](int e) { /* NO-OP */ });

		EventQueue<int> queue;
		EXPECT_EQ(0, queue.connected_count());

		queue.connect(handler);

		EXPECT_EQ(1, queue.connected_count());

		delete handler;
	}

	TEST(EventQueueUnitTest, PushEvent) {
		EventHandler<int> handler([](int e) { /* NO-OP */ });

		EventQueue<int> queue;
		EXPECT_EQ(0, queue.get_event_count());

		queue.push(45);
		queue.push(94);
		EXPECT_EQ(2, queue.get_event_count());

		queue.push(84654);
		queue.push(537837);
		queue.push(4534538);
		EXPECT_EQ(5, queue.get_event_count());
	}

	TEST(EventQueueUnitTest, FlushEvents) {
		int modify = 0;

		EventHandler<int> handler([&modify](int e) { modify = modify + e; });

		EventQueue<int> queue;
		EXPECT_EQ(0, queue.get_event_count());
		EXPECT_EQ(0, queue.connected_count());

		queue.connect(&handler);
		EXPECT_EQ(1, queue.connected_count());

		queue.push(45);
		EXPECT_EQ(0, modify);
		EXPECT_EQ(1, queue.get_event_count());

		queue.push(45);
		EXPECT_EQ(0, modify);
		EXPECT_EQ(2, queue.get_event_count());

		queue.flush();
		EXPECT_EQ(90, modify);
		EXPECT_EQ(0, queue.get_event_count());

		queue.push(-45);
		EXPECT_EQ(90, modify);
		EXPECT_EQ(1, queue.get_event_count());

		queue.flush();
		EXPECT_EQ(45, modify);
		EXPECT_EQ(0, queue.get_event_count());
	}

}
