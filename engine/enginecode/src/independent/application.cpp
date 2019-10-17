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

	void Application::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::WindowResize) {
			WindowResizeEvent re = (WindowResizeEvent&)e;

			NG_INFO("Window Resize Event. Width {0}. Height {1}", re.getWidth(), re.getHeight());
		}
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
				WindowResizeEvent e(1024, 720);
				onEvent(e);
				run = false;
				NG_INFO("Time Elapsed: {0}. Shutting Down", accumulatedTime);
			}


		}
	}

}
