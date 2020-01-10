/*! \file inputPoller
* This file will handle the inputs outlined in the events systems
*/
#pragma once
#include <glm/glm.hpp>
#include "systems\Codes.h"

namespace Engine {

	/*! \class InputPoller
	* This will take the events and poll it.
	* This works for Keyboard, Mouse and Window.
	*/
	class InputPoller
	{
	private:
		static InputPoller* s_instance; //!< static pointer to s_instance

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0; //!< boolean value isKeyPressed
		virtual bool isMouseButtonPressedImpl(int button) = 0; //!< boolean value for isMouseButtonPressed
		virtual glm::vec2 getMousePositionImpl() = 0; //!< vec2 got getting mouse position
		virtual float getMouseXImpl() = 0; //!< float vlaue for mouse X position
		virtual float getMouseYImpl() = 0; //!< float vlaue for mouse Y position

	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); } //!< returns boolean value for if the key is pressed
		inline static bool isMousePressed(int button) { return s_instance->isMouseButtonPressedImpl(button); } //!< returns boolean value for if the mouse buttons has been pressed
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImpl(); } //!< returns value for mouse position
		inline static float getMouseX() { return s_instance->getMouseX(); } //!< returns value for the mouse X position
		inline static float getMouseY() { return s_instance->getMouseY(); }	//!< returns value for the mouse Y position
	};
}