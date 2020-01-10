/*! \file Timer.h
* This file contains the Timer class
*/
#pragma once
#include "systems\system.h"
#include <chrono>

namespace Engine {

	/*! \class timer
	* This class will start a timer, and also count the elapsed time.
	*/
	class timer : System 
	{
	private:
		static std::chrono::high_resolution_clock::time_point startTimer; //!< Chrono function to start timer
		static std::chrono::high_resolution_clock::time_point endTimer; //!< Chrono function to end timer
		static std::chrono::duration<float> time_Passed; //<! chrono function to find time passed

		static bool bRunning; //!< boolean value for bRunning

		
	public:

		static void start(SystemSignal init = SystemSignal::None); //!< Start the system
		static void stop(SystemSignal close = SystemSignal::None); //!< Stop the system
		static float GetSeconds() { return time_Passed.count(); } //!< float to return amount of time passed, in seconds
		static void Update(); //!< void function for update


	};


}


