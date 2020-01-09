/*! \file window.h
* This file contains classes associated with drawing a window
* The window will contain the rendered scene.
*/
#pragma once

#include "graphicsContext.h"
#include <string>
#include <functional>
#include "systems\system.h"
#include "Events\events.h"

namespace Engine {

	/*! \class WindowSystem
	* This class will check to see if the window system is on or off.
	*/
	class WindowSystem : public System {
	private:
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Stop the system
		virtual bool isActive() const = 0;
	};

	/*! \class WindowProperties
	* This class contains all the information for the window.
	*/
	struct WindowProperties
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_isFullScreen;
		bool m_isVSync;

		WindowProperties(const std::string& title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : 
			m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen) {}
	};

	/*! \class Window
	* This class contains the Window Events, and how they are used.
	*/
	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0;
		virtual void close() = 0;
		virtual ~Window() {};
		virtual void onUpdate(float timestep) = 0;
		virtual void onResize(unsigned int width, unsigned int height) = 0;
		virtual void setVSync(bool VSync) = 0;
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual void* getNativeWindow() const = 0;
		virtual bool isFullScreenMode() const = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProperties& properties = WindowProperties());
	protected:
		std::shared_ptr<GraphicsContext> m_context;
	};
}

