/** \file application.h
* This is the main file for the system
*/
#pragma once
#include "Events/events.h"
#include "Events/Window_Events.h"
#include "Events/Keyboard_Events.h"
#include "Events/Mouse_Events.h"
#include "windows\window.h"
#include "Renderer\Texture.h"
#include "Renderer\Shader.h"
#include "Renderer\VertexArray.h"
#include "Renderer\Material.h"
#include "Renderer\Renderer.h"
#include "windows\PerspectiveCamera3D.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Here the textures and shaders are applied.
	The various events can also be found here.
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
	private:
		static Application* s_instance; //!< Singleton instance of the application
		static float accumulatedTime; //!< float of accumulatedTime, or time passed
		bool m_Running; //!< boolean for m_Running
		std::shared_ptr<WindowSystem> m_windowSys; //!< Shared Pointer to WindowSystem
		std::unique_ptr<Window> m_window; //!< Unique pointer of Window
		

		std::shared_ptr<FPSCameraControllerEuler> m_camera; //!< Camera Controller (3D)
		std::shared_ptr<VertexArray> m_FCVA; //!< FCVA - Flat Colour Vertex Array
		std::shared_ptr<VertexArray> m_TPVA; //!< TPVA - Textured Phong Vertex Array
		std::shared_ptr<Texture> m_numberTexture; //!< Number Texture for cube
		std::shared_ptr<Texture> m_letterTexture; //!< Letter Texture for cube
		
		std::shared_ptr<Shader> m_FCprogram; //!< FCShader - Flat Colour Shader
		std::shared_ptr<Shader> m_TPprogram; //!< TPShader - Textued Phong Shader

		std::shared_ptr<Material> m_FCmaterial; //!< FCShader - Flat Colour material
		std::shared_ptr<Material> m_TPmaterial; //!< TPShader - Textued Phong material

		std::shared_ptr<Renderer> m_renderer; //!< FCShader - Flat Colour Shader
		
		static float s_timestep; //!< float variable for timestep

		
#pragma region TempVars
		// Temp stuff
		std::shared_ptr<VertexArray> m_FCvertexArray; //!< Flat Colour VAO
		std::shared_ptr<VertexBuffer> m_FCvertexBuffer;//!< Flat Colour VBO
		std::shared_ptr<VertexArray> m_TPvertexArray; //!< Textured Phong VAO
		std::shared_ptr<VertexBuffer> m_TPvertexBuffer;//!< Textured Phong VBO
		std::shared_ptr<IndexBuffer> m_FCindexBuffer; //!< Index buffer for colour cube
		std::shared_ptr<IndexBuffer> m_TPindexBuffer; //!< Index buffer for texture Phong cube
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?
#pragma endregion TempVars


	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline static float getTimestep() { return s_timestep; } //!< getsTimestep, returns s_timestep
		inline Window& getWindow() { return *m_window; } //!< getWindow, returns m_window
		void run(); //!< Main loop
		void onEvent(Event& e);//!< Event Function

		//!< Window Events Here
		bool onCloseWindow(WindowCloseEvent& e);
		bool onResizeWindow(WindowResizeEvent& e);
		bool onFocusWindow(WindowFocusEvent& e);
		bool onLostFocusWindow(WindowLostFocusEvent& e);
		bool onMovedWindow(WindowMovedEvent& e);

		//!< Keyboard Events here
		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent& e);
		bool onKeyTyped(KeyTypedEvent& e);

		//!< Mouse Events Here
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}