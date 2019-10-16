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

	

	void Application::run()
	{

		bool run = true;
		while(run) {
			Engine::timer::Update();
			float timestep = Engine::timer::GetSeconds();
			float FPS = 1.0f / timestep;
			NG_INFO("FPS: {0}", FPS);
		}
	}

}
