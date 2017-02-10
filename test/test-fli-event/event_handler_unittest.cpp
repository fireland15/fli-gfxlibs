#include <functional>

#include <gtest\gtest.h>
#include <fli-event\event_handler.hpp>

namespace {

	using namespace events;
	
	/*************************************************************
	* Testing EventHandler<> Methods
	**************************************************************/

	TEST(EventHandlerUnitTest, HandlerId) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1([](int e) { /* NO-OP */ });
		EventHandler<int> handler2([](int e) { /* NO-OP */ });
		EventHandler<int> handler3([](int e) { /* NO-OP */ });
		EventHandler<double> handler4([](double e) { /* NO-OP */ });

		EXPECT_EQ(0, handler0.get_id());
		EXPECT_EQ(1, handler1.get_id());
		EXPECT_EQ(2, handler2.get_id());
		EXPECT_EQ(3, handler3.get_id());
		EXPECT_EQ(4, handler4.get_id());
	}

	TEST(EventHandlerUnitTest, NotEqualsOperator_True) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1([](int e) { /* NO-OP */ });

		EXPECT_TRUE(handler0 != handler1);
	}

	TEST(EventHandlerUnitTest, NotEqualsOperator_False) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1 = handler0;

		EXPECT_FALSE(handler0 != handler1);
	}

	TEST(EventHandlerUnitTest, EqualsOperator_True) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1 = handler0;
		

		EXPECT_TRUE(handler0 == handler1);
	}

	TEST(EventHandlerUnitTest, EqualsOperator_False) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1([](int e) { /* NO-OP */ });


		EXPECT_FALSE(handler0 == handler1);
	}

	TEST(EventHandlerUnitTest, Invoke) {
		int i = 3;

		EventHandler<int> handler([&i](int e) { i = i + e; });

		handler.invoke(7);

		EXPECT_EQ(10, i);
	}

	TEST(EventHandlerUnitTest, GetEventTypeHashCode) {
		EventHandler<int> handler([](int e) { /* NO-OP */ });

		size_t typeHash = typeid(int).hash_code();

		EXPECT_EQ(typeHash, handler.get_event_type_hashcode());
	}

	/*************************************************************
	* Testing IEventHandler interface methods
	**************************************************************/

	TEST(IEventHandlerUnitTest, EqualsOperator_False) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1([](int e) { /* NO-OP */ });

		IEventHandler& ihandler0 = handler0;
		IEventHandler& ihandler1 = handler1;

		EXPECT_FALSE(ihandler0 == ihandler1);
	}

	TEST(IEventHandlerUnitTest, EqualsOperator_True) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1 = handler0;

		IEventHandler& ihandler0 = handler0;
		IEventHandler& ihandler1 = handler1;

		EXPECT_TRUE(ihandler0 == ihandler1);
	}

	TEST(IEventHandlerUnitTest, NotEqualsOperator_False) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1 = handler0;

		IEventHandler& ihandler0 = handler0;
		IEventHandler& ihandler1 = handler1;

		EXPECT_FALSE(ihandler0 != ihandler1);
	}
	
	TEST(IEventHandlerUnitTest, NotEqualsOperator_True) {
		EventHandler<int> handler0([](int e) { /* NO-OP */ });
		EventHandler<int> handler1([](int e) { /* NO-OP */ });

		IEventHandler& ihandler0 = handler0;
		IEventHandler& ihandler1 = handler1;

		EXPECT_TRUE(ihandler0 != ihandler1);
	}

	TEST(IEventHandlerUnitTest, GetEventTypeHashCode) {
		EventHandler<int> handler([](int e) { /* NO-OP */ });

		IEventHandler& ihandler = handler;

		size_t typeHash = typeid(int).hash_code();

		EXPECT_EQ(typeHash, ihandler.get_event_type_hashcode());
	}
}