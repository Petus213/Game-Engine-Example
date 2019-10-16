#include "engine_pch.h"
#include "systems\system.h"
#include "..\..\include\independent\systems\Timer.h"

namespace Engine {

	std::chrono::high_resolution_clock::time_point timer::startTimer;
	std::chrono::high_resolution_clock::time_point timer::endTimer;
	std::chrono::duration<float> timer::framePassed;

	bool timer::bRunning = false;

	void timer::start(SystemSignal init)
	{
		bRunning = true;
		startTimer = std::chrono::high_resolution_clock::now();

	}

	void timer::stop(SystemSignal close)
	{
		bRunning = false;
	}

	void timer::Update()
	{
		if (bRunning) {
			endTimer = std::chrono::high_resolution_clock::now();
			framePassed = endTimer - startTimer;

			startTimer = std::chrono::high_resolution_clock::now();
		}


	}

}