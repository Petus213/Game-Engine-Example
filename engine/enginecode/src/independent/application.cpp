/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"
#include "systems\log.h"
#include "systems\Timer.h"

namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()//constructor
	{
		Engine::Log::start();
		NG_INFO("Application Starting...");

		Engine::timer::start();

		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
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
		NG_INFO("Key has been pressed", e.getKeycode(), e.getRepeatCount());
		return true;
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
		NG_INFO("Mouse has moved", e.getMouseXoffset(), e.getMouseYoffset());
		return true;
	}
	
	bool Application::onMouseScrolled(MouseScrolledEvent & e)
	{
		NG_INFO("Mouse has scrolled", e.getMouseXoffset(), e.getMouseYoffset());
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
		dispatcher.dispatch<MouseButtonReleasedEvent>(std::bind(&Application:: onMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMovedEvent>(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolledEvent>(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));
	}



	void Application::run()
	{
		float accumulatedTime = 0.f;
		bool run = true;
		while(run) {
			
			Engine::timer::Update();
			float timestep = Engine::timer::GetSeconds();
			accumulatedTime += timestep;
			NG_INFO("FPS: {0}. Time Elapsed: {1}.", (int)(1.0f / timestep), accumulatedTime);

			m_window->onUpdate(timestep);
			
			if (accumulatedTime > 10.f)
			{
				WindowResizeEvent e1(1024, 720);
				onEvent(e1);
				WindowCloseEvent e2;
				onEvent(e2);
				
			}


		}
	}

}
