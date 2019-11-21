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

		static float s_timestep;

#pragma region TempVars
		// Temp stuff
		unsigned int m_FCvertexArray; // Flat Colour VAO
		unsigned int m_FCvertexBuffer;// Flat Colour VBO
		unsigned int m_TPvertexArray; // Textured Phong VAO
		unsigned int m_TPvertexBuffer;// Textured Phong VBO
		unsigned int m_FCindexBuffer; // Index buffer for colour cube
		unsigned int m_TPindexBuffer; // Index buffer for texture Phong cube
		unsigned int m_FCprogram; // Flat colour shader ID
		unsigned int m_TPprogram; // Textured Phong shader ID
		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?
#pragma endregion TempVars


	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline static float getTimestep() { return s_timestep; }
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