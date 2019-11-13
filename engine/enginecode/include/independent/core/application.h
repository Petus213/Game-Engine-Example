/** \file application.h
*/
#pragma once
#include "Events/events.h"
#include "Events/Window_Events.h"
#include "Events/Keyboard_Events.h"
#include "Events/Mouse_Events.h"
#include "windows\window.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
	private:
		static Application* s_instance; //!< Singleton instance of the application
		static float accumulatedTime;
		bool m_Running;
		std::shared_ptr<WindowSystem> m_windowSys;
		std::unique_ptr<Window> m_window;

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline Window& getWindow() { return *m_window; }
		void run(); //!< Main loop
		void onEvent(Event& e);

		//Window Events Here
		bool onCloseWindow(WindowCloseEvent& e);
		bool onResizeWindow(WindowResizeEvent& e);
		bool onFocusWindow(WindowFocusEvent& e);
		bool onLostFocusWindow(WindowLostFocusEvent& e);
		bool onMovedWindow(WindowMovedEvent& e);

		//Keyboard Events here
		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent& e);
		bool onKeyTyped(KeyTypedEvent& e);

		//Mouse Events Here
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}