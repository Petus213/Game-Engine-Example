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
	}

	Application::~Application()
	{
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		NG_INFO("Closing Application");
		m_Running = false;
		return true;
	}

	bool Application::onResize(WindowResizeEvent & e)
	{
		NG_INFO("Resize Window to {0}x{1}", e.getWidth(), e.getHeight());
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
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
