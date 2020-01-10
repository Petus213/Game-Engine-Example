/*! \file GLFW_Windows.h
* This file is for the Window of the system, but only with an OpenGL renderer.
*/
#pragma once
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "windows\window.h"



namespace Engine {
	/*! \class GLFWWindowSystem
	*	This class inherits from the WindowSystem
	* It will only work with the OpenGL renderer.
	*/
	class GLFWWindowSystem : public WindowSystem {
	private:
		static bool m_active; //!< bool m_active - returns boolean for if window is active.
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override; //!< void function start - starts window
		void stop(SystemSignal close = SystemSignal::None, ...) override; //!< void function stop - stops window
		inline bool isActive() const override { return m_active; }; //!< bool isActive - returns a boolean for m_active
	};

	/*! \class GLFWWindowImpl
	* This class inherits from the Window class
	* It will only work with the OpenGL renderer
	* It manages the functions with the window events.
	*/
	class GLFWWindowImpl : public Window
	{
	private:
		GLFWwindow* m_nativeWindow; //!< Pointer to m_nativeWindow

		void init(const WindowProperties& properties) override; //!< void function init
		void close(); //!< void function close
		WindowProperties m_properties; //!< m_properties from base window class
		std::function<void(Event&)> m_callback; //!< function for m_callback
		float m_aspectRatio; //!< float m_aspectRatio
	public:
		GLFWWindowImpl(const WindowProperties & properties); //!< Constructor
		~GLFWWindowImpl(); //!< Destructor
		void onUpdate(float timestep) override; //!< void function for onUpdate
		void onResize(unsigned int width, unsigned int height) override; //!< void function for onResize
		void setVSync(bool VSync) override; //!< void function for setVSync
		void setEventCallback(const std::function<void(Event&)>& callback) override; //!< void function for setEventCallback
		inline unsigned int getWidth() const override { return m_properties.m_width; } //!< returns value for getWidth
		inline unsigned int getHeight() const override { return m_properties.m_height; } //!< returns value for getHeight
		inline void* getNativeWindow() const override { return m_nativeWindow; } //!< void function for getNativeWindow
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; } //!< returns boolean value for if it is in full screen mode
		inline bool isVSync() const override { return m_properties.m_isVSync; } //!< returns boolean value for if Vsync is on
	};

}
