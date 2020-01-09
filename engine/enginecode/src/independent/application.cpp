/** \file application.cpp
*/


#include "engine_pch.h"

#pragma region TempIncludes
// temp includes
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma endregion TempIncludes

#include "core/application.h"
#include "systems\log.h"
#include "systems\Timer.h"
#include "windows\GLFWCodes.h"


#ifdef NG_PLATFORM_WINDOWS
#include "windows\GLFW_Windows.h"
#endif 

namespace Engine {
	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 0.f;

#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application::Application()//constructor
	{
		Engine::Log::start();
		NG_INFO("Application Starting...");

		Engine::timer::start();

		if (s_instance == nullptr)
		{
			s_instance = this;
		}

#ifdef NG_PLATFORM_WINDOWS
		m_windowSys = std::shared_ptr<WindowSystem>(new GLFWWindowSystem());
#endif
		m_windowSys->start();
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		
		

#pragma region TempSetup
		//  Temporary set up code to be abstracted
		m_renderer = std::shared_ptr<Renderer>(Renderer::createBasic3D());

		m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(RenderCommand::setBackfaceCullingCommand(true));

		m_FCvertexArray.reset(VertexArray::create());
		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		m_FCvertexBuffer.reset(VertexBuffer::create(FCvertices, sizeof(FCvertices)));
		m_FCprogram.reset(Shader::create("assets/shaders/flatColour.glsl"));
		m_FCvertexBuffer->SetLayout(m_FCprogram->getBufferLayout());
		m_FCvertexArray->setVertexBuffer(m_FCvertexBuffer);

		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};

		m_FCindexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_FCvertexArray->setIndexBuffer(m_FCindexBuffer);

		m_TPvertexArray.reset(VertexArray::create());

		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};

		m_TPvertexBuffer.reset(VertexBuffer::create(TPvertices, sizeof(TPvertices)));
		m_TPprogram.reset(Shader::create("assets/shaders/texturedPhong.glsl"));
		m_TPvertexBuffer->SetLayout(m_TPprogram->getBufferLayout());
		m_TPvertexArray->setVertexBuffer(m_TPvertexBuffer);
		m_TPindexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_TPvertexArray->setIndexBuffer(m_TPindexBuffer);
		m_letterTexture.reset(Texture::createFromFile("assets/textures/letterCube.png"));
		m_numberTexture.reset(Texture::createFromFile("assets/textures/numberCube.png"));
		
		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

		m_FCmaterial.reset(Material::create(m_FCprogram, m_FCvertexArray));
		m_TPmaterial.reset(Material::create(m_TPprogram, m_TPvertexArray));
#pragma endregion TempSetup

	}

	Application::~Application()
	{
	}

	//Window Events Here
	bool Application::onCloseWindow(WindowCloseEvent & e)
	{
		NG_INFO("Closing Application");
		m_Running = false;
		return true;
	}

	bool Application::onResizeWindow(WindowResizeEvent & e)
	{
		m_window->onResize(e.getWidth(), e.getHeight());
		NG_INFO("Resize Window to {0}x{1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onFocusWindow(WindowFocusEvent & e)
	{
		NG_INFO("Window Focus Perfect");
		return true;
	}

	bool Application::onLostFocusWindow(WindowLostFocusEvent & e)
	{
		NG_INFO("Window Lost Focus");
		return true;
	}

	bool Application::onMovedWindow(WindowMovedEvent & e)
	{
		NG_INFO("Window has been moved");
		return true;
	}

	//Keyboard Events Here
	bool Application::onKeyPressed(KeyPressedEvent & e)
	{
		if (e.getKeycode() == KEY_ESCAPE) {
			NG_INFO("CLosing Application");
			m_window->close();
			return true;
		}
		return false;
	}

	bool Application::onKeyReleased(KeyReleasedEvent & e)
	{
		NG_INFO("Key has been released", e.getKeycode());
		return true;
	}

	bool Application::onKeyTyped(KeyTypedEvent & e)
	{
		NG_INFO("Keys have been typed", e.getKeycode());
		return true;
	}

	//Mouse Events here
	bool Application::onMouseButtonPressed(MouseButtonPressedEvent & e)
	{
		NG_INFO("Mouse Button has been pressed", e.getMouseButton());
		return true;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent & e)
	{
		NG_INFO("Mouse button has been released", e.getMouseButton());
		return true;
	}

	bool Application::onMouseMoved(MouseMovedEvent & e)
	{
		NG_INFO("Mouse has moved to {0}x{1}", e.getMouseXoffset(), e.getMouseYoffset());
		return true;
	}

	bool Application::onMouseScrolled(MouseScrolledEvent & e)
	{
		NG_INFO("Mouse has scrolled to {0}x{1}", e.getMouseXoffset(), e.getMouseYoffset());
		return true;
	}




	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//Window Events Dispatched
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onCloseWindow, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResizeWindow, this, std::placeholders::_1));
		dispatcher.dispatch<WindowFocusEvent>(std::bind(&Application::onFocusWindow, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocusEvent>(std::bind(&Application::onLostFocusWindow, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMovedEvent>(std::bind(&Application::onMovedWindow, this, std::placeholders::_1));

		//KeyBoard Events Dispatched
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleasedEvent>(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<KeyTypedEvent>(std::bind(&Application::onKeyTyped, this, std::placeholders::_1));

		//Mouse Events Dispatched
		dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleasedEvent>(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMovedEvent>(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolledEvent>(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));
	}



	void Application::run()
	{
		float accumulatedTime = 0.f;
		bool run = true;
		while (run) {

			Engine::timer::Update();
			float s_timestep = Engine::timer::GetSeconds();
			//ENGINE_INFO("FPS: {0}", (int)(1.0f / s_timestep));

#pragma region TempDrawCode
// Temporary draw code to be abstracted

			m_renderer->actionCommand(RenderCommand::setClearColourCommand(.8f, .8f, .8f, 1.f));
			m_renderer->actionCommand(RenderCommand::ClearDepthColourBufferCommand());

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move, you can ignore this more or less.
			glm::mat4 FCtranslation, TPtranslation;

			if (m_goingUp)
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
			}
			else
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
			}

			m_timeSummed += s_timestep;
			if (m_timeSummed > 20.0f) {
				m_timeSummed = 0.f;
				m_goingUp = !m_goingUp;
			}


			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

			// End of code to make the cube move.

			glm::mat4 fcMVP = projection * view * FCmodel;
			
			m_FCmaterial->setDataElement("u_MVP", (void*)&fcMVP[0][0]);
			
			m_renderer->submit(m_FCmaterial);

			glm::mat4 tpMVP = projection * view * TPmodel;
			unsigned int texSlot;
			if (m_goingUp) texSlot = m_textureSlots[0];
			else texSlot = m_textureSlots[1];

			m_TPprogram->bind();
			m_TPvertexArray->bind();

			m_TPmaterial->setDataElement("u_MVP", (void *)&tpMVP[0][0]);
			m_TPmaterial->setDataElement("u_model", (void *)&TPmodel[0][0]);

			glm::vec3 lightPos = glm::vec3(0.f, 1.f, 5.f);
			glm::vec3 viewPos = glm::vec3(0.f, 0.f, -4.5f);
			glm::vec3 lightColour = glm::vec3(1.f, 1.f, 1.f);

			m_TPmaterial->setDataElement("u_lightPos", (void*)&lightPos[0]);
			m_TPmaterial->setDataElement("u_viewPos", (void*)&viewPos[0]);
			m_TPmaterial->setDataElement("u_lightColour", (void*)&lightColour[0]);
			m_TPmaterial->setDataElement("u_texData", (void*)&texSlot);

			m_renderer->submit(m_TPmaterial);



			// End temporary code
#pragma endregion TempDrawCode

			m_window->onUpdate(s_timestep);

		}
	}

}