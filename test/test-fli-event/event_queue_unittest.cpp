#include <functional>

#include <gtest\gtest.h>
#include <fli-event\event_queue.hpp>
#include <fli-event\event_handler.hpp>

namespace {

	TEST(EventQueueUnitTest, ConnectCallback) {
		events::EventHandler<int> handler([](int e) { /* NO-OP */ });

		events::EventQueue<int> queue;
		EXPECT_EQ(0, queue.connected_count());

		queue.connect((events::IEventHandler*)&handler);

		EXPECT_EQ(1, queue.connected_count());
	}

}
