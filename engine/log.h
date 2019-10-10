#pragma once
#include <systems/system.h>
#include <spdlog/spdlog.h>


namespace Engine {

	class Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_Enginelogger;
		static std::shared_ptr<spdlog::logger> s_Applogger;
		bool bRunning;

	public:
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_Enginelogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_Applogger; }
		bool bRunning() { return bRunning; }
		static void Init();
	};

}

//Macros
//Engine Log Macros

#define HZ_CORE_TRACE(...) ::Engine::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...) ::Engine::Logger::GetCoreLogger()->info(__VA_ARGS__)