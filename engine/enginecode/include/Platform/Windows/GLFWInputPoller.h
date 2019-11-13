#pragma once
#include "systems\inputPoller.h"

namespace Engine {

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