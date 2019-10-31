#pragma once
#include <glm/glm.hpp>

namespace Engine {

	class InputPoller
	{
	private:
		static InputPoller* s_instance;

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual glm::vec2 getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
		inline static bool isMousePressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImpl(); }
		inline static float getMouseXImpl() { return s_instance->getMouseXImpl(); }
		inline static float getMouseYImpl() { return s_instance->getMouseYImpl(); }
	};
}