#pragma once
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "windows\window.h"



namespace Engine {

	class GLFWWindowSystem : public WindowSystem {
	private:
		static bool m_active;
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override; 
		void stop(SystemSignal close = SystemSignal::None, ...) override; 
		inline bool isActive() const override { return m_active; };
	};

	class GLFWWindowImpl : public Window
	{
	private:
		GLFWwindow* m_nativeWindow;

		void init(const WindowProperties& properties) override;
		void close();
		WindowProperties m_properties;
		std::function<void(Event&)> m_callback;
		float m_aspectRatio;
	public:
		GLFWWindowImpl(const WindowProperties & properties);
		~GLFWWindowImpl();
		void onUpdate(float timestep) override;
		void onResize(unsigned int width, unsigned int height) override;
		void setVSync(bool VSync) override;
		void setEventCallback(const std::function<void(Event&)>& callback) override;
		inline unsigned int getWidth() const override { return m_properties.m_width; }
		inline unsigned int getHeight() const override { return m_properties.m_height; }
		inline void* getNativeWindow() const override { return m_nativeWindow; }
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; }
		inline bool isVSync() const override { return m_properties.m_isVSync; }
	};

}