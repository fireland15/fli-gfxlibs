#include <gtest\gtest.h>
#include <fli-event\event_broadcaster.hpp>

namespace {

	using namespace events;

	TEST(EventBroadcasterBuilderUnittest, MakesWithRightNumberOfQueues) {
		EventBroadcaster::EventBroadcasterBuilder builder;
		EventBroadcaster broadcaster = builder.AddEventQueue<int>().AddEventQueue<float>().Build();

		EXPECT_EQ(2, broadcaster.queue_count());
	}

	TEST(EventBroadcasterUnittest, BroadcastsEvents) {
		EventBroadcaster::EventBroadcasterBuilder builder;
		EventBroadcaster broadcaster = builder.AddEventQueue<int>().AddEventQueue<float>().Build();

		int h1 = 0;
		int f1 = 0;

		EventHandler<int> handler1([&h1](int x) { h1 += x; });
		EventHandler<int> handler2([&h1](int x) { h1 += x; });
		EventHandler<float> handler3([&f1](float x) { f1 += x; });
		EventHandler<float> handler4([&f1](float x) { f1 += x; });

		broadcaster.connect(&handler1);
		broadcaster.connect(&handler2);
		broadcaster.connect(&handler3);
		broadcaster.connect(&handler4);

		broadcaster.push(42);
		broadcaster.push(34.0f);

		broadcaster.flush_events();

		EXPECT_EQ(84, h1);
		EXPECT_EQ(68.0f, f1);
	}

}