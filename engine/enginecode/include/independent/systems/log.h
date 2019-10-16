#pragma once
#include <systems/system.h>
#include <spdlog/spdlog.h>

namespace Engine {
	class Log:System
	{
	private:
		static bool bRunning;
		static std::shared_ptr<spdlog::logger> s_log;

	public:

		static bool Running() { return bRunning; }
		static std::shared_ptr<spdlog::logger>& GetLog() { return s_log; }
		static void start(SystemSignal init = SystemSignal::None); //!< Start the system
		static void stop(SystemSignal close = SystemSignal::None); //!< Stop the system
	};

}

//Macros
#define NG_TRACE(...)::Engine::Log::GetLog()->trace(__VA_ARGS__)
#define NG_INFO(...)::Engine::Log::GetLog()->info(__VA_ARGS__)
#define NG_WARN(...)::Engine::Log::GetLog()->warn(__VA_ARGS__)
#define NG_ERROR(...)::Engine::Log::GetLog()->error(__VA_ARGS__)
#define NG_CRITICAL(...)::Engine::Log::GetLog()->critical(__VA_ARGS__)
#define NG_FATAL(...)::Engine::Log::GetLog()->fatal(__VA_ARGS__)