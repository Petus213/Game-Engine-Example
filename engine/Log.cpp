#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> s_Enginelogger;
	std::shared_ptr<spdlog::logger> s_Applogger;

	void Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Enginelogger = spdlog::stdout_color_mt("ENGINE");
		s_Enginelogger->set_level(spdlog::level::trace);

		s_Applogger = spdlog::stdout_color_mt("APP");
		s_Applogger->set_level(spdlog::level::trace);
	}



}