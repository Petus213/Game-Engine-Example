#pragma once
#include <gtest\gtest.h>
#include "Events\events.h"
#include "Events\Window_Events.h"



const int width = 1024;
const int height = 720;

Engine::WindowResizeEvent re(width, height);
Engine::WindowCloseEvent ce;
Engine::WindowFocusEvent fe;
Engine::WindowMovedEvent me;

bool OnCloseTrue(Engine::WindowCloseEvent& e)
{
	return true;
}

bool OnCloseFalse(Engine::WindowCloseEvent& e)
{
	return false;
}

bool OnResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}

bool OnResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}

bool onFocusTrue(Engine::WindowFocusEvent& e)
{
	return true;
}

bool onFocusFalse(Engine::WindowFocusEvent& e)
{
	return false;
}

bool onMoveTrue(Engine::WindowMovedEvent& e)
{
	return true;
}

bool onMoveFalse(Engine::WindowMovedEvent& e)
{
	return false;
}