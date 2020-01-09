/*! \file GLFWInputPoller.h
* This file is for the Input Poller specifically to make use with OpenGL
*/
#pragma once
#include "systems\inputPoller.h"

namespace Engine {

	/*! \class GLFWInputPoller
	* This class inherits from the Input Poller class
	* It works only for OpenGL
	*/
	class GLFWInputPoller : public InputPoller
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual glm::vec2 getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};
}