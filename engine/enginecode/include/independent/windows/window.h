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
		virtual bool isActive() const = 0; //!< boolean value for if the system is active
	};

	/*! \class WindowProperties
	* This class contains all the information for the window.
	*/
	struct WindowProperties
	{
		std::string m_title; //!< string variable for m_title
		unsigned int m_width; //!< integer value for width
		unsigned int m_height; //!< integer value for height
		bool m_isFullScreen; //!< boolean variable for full screen
		bool m_isVSync; //!< boolean variable for V sync

		WindowProperties(const std::string& title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : 
			m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen) {} //!< Setting the window properties
	};

	/*! \class Window
	* This class contains the Window Events, and how they are used.
	*/
	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< void function for initilisation
		virtual void close() = 0; //!< void function for closing window
		virtual ~Window() {}; //!< destructor
		virtual void onUpdate(float timestep) = 0; //!< void function for Update
		virtual void onResize(unsigned int width, unsigned int height) = 0; //!< void function for Resizing window
		virtual void setVSync(bool VSync) = 0; //!< void function for settting V Sync
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0; //!< void function for setting callback
		virtual unsigned int getWidth() const = 0; //!< integer value for getting width
		virtual unsigned int getHeight() const = 0; //!< integer value for getting height
		virtual void* getNativeWindow() const = 0; //!< void pointer to getting Native Window
		virtual bool isFullScreenMode() const = 0; //!< boolean value for Full Screen Mode
		virtual bool isVSync() const = 0; //!< boolean value for V sync

		static Window* create(const WindowProperties& properties = WindowProperties()); //!<  create Window
	protected:
		std::shared_ptr<GraphicsContext> m_context; //!< shared pointer to m_context from Graphics Context
	};
}

