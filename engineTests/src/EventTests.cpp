#include "EventTests.h"

TEST(Events, DispatchCloseTrue)
{
	Engine::EventDispatcher dispatcher(ce);
	bool result = dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(OnCloseTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}
TEST(Events, DispatchCloseFalse)
{
	Engine::EventDispatcher dispatcher(ce);
	bool result = dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(OnCloseFalse, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, ResizeConstructor)
{
	int gotWidth = re.getWidth();
	int gotHeight = re.getHeight();
	Engine::EventType type = re.getEventType();

	EXPECT_EQ(gotWidth, width);
	EXPECT_EQ(gotHeight, height);
}

TEST(Events, DispatchTrue) {
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchFalse) {
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleTrue)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_TRUE(result);
}
TEST(Events, DispatchHandleFalse)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeFalse, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_FALSE(result);
}

TEST(Events, DispatchFocusTrue)
{
	Engine::EventDispatcher dispatcher(fe);
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onFocusTrue, std::placeholders::_1));
	bool result = fe.handled();
	EXPECT_TRUE(result);
}
TEST(Events, DispatchFocusFalse)
{
	Engine::EventDispatcher dispatcher(fe);
	dispatcher.dispatch<Engine::WindowFocusEvent>(std::bind(onFocusFalse, std::placeholders::_1));
	bool result = fe.handled();
	EXPECT_FALSE(result);
}

TEST(Events, DispatchMoveTrue)
{
	Engine::EventDispatcher dispatcher(me);
	dispatcher.dispatch<Engine::WindowMovedEvent>(std::bind(onMoveTrue, std::placeholders::_1));
	bool result = me.handled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchMoveFalse)
{
	Engine::EventDispatcher dispatcher(me);
	dispatcher.dispatch<Engine::WindowMovedEvent>(std::bind(onMoveTrue, std::placeholders::_1));
	bool result = me.handled();
	EXPECT_FALSE(result);
}