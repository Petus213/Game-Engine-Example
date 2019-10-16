#include "engine_pch.h"
#include "systems\log.h"
#include "spdlog/sinks/stdout_color_sinks.h"



namespace Engine {

	bool Log::bRunning = false;
	std::shared_ptr<spdlog::logger> Log::s_log;

	void Log::start(SystemSignal init)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_log = spdlog::stdout_color_mt("ENGINE");
		s_log->set_level(spdlog::level::trace);
		bRunning = true;
	}

	void Log::stop(SystemSignal close)
	{
		bRunning = false;
		s_log.reset();
	}

}