#pragma once

namespace Engine {

	class GLFWInputPoller : public InputPoller
	{
	protected:
		bool isKeyPressedImpl(int keycode) override;
		bool isMouseButtonPressedImpl(int button) override;
		glm::vec2 getMousePositionImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;
	};
}