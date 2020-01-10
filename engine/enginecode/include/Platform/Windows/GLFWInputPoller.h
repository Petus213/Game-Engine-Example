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
		virtual bool isKeyPressedImpl(int keycode) override; //!< bool isKeyPressedImpl - Boolean for if the key is pressed.
		virtual bool isMouseButtonPressedImpl(int button) override; //!< bool isM<ouseButtonPressedImpl - boolean for if the mouse button is pressed.
		virtual glm::vec2 getMousePositionImpl() override; //!< vec2 getMousePositionImpl - used in getting mouse position
		virtual float getMouseXImpl() override; //!< float getMouseXImple - Used for finding mouse position on X axis
		virtual float getMouseYImpl() override;	//!< float getMouseYImple - Used for finding mouse position on Y axis
	};
}