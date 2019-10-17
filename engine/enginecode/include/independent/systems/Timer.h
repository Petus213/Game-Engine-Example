#pragma once
#include "systems\system.h"
#include <chrono>

namespace Engine {

	class timer : System 
	{
	private:
		static std::chrono::high_resolution_clock::time_point startTimer;
		static std::chrono::high_resolution_clock::time_point endTimer;
		static std::chrono::duration<float> time_Passed;

		static bool bRunning;

		
	public:

		static void start(SystemSignal init = SystemSignal::None); //!< Start the system
		static void stop(SystemSignal close = SystemSignal::None); //!< Stop the system
		static float GetSeconds() { return time_Passed.count(); }
		static void Update();


	};


}


