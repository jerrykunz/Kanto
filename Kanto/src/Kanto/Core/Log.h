#pragma once
#include <Kanto/Core/Base.h>
#include <spdlog/spdlog.h>
//#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Kanto
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define KN_CORE_TRACE(...)		Kanto::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define KN_CORE_INFO(...)		Kanto::Log::GetCoreLogger()->info(__VA_ARGS__);
#define KN_CORE_WARN(...)		Kanto::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define KN_CORE_ERROR(...)		Kanto::Log::GetCoreLogger()->error(__VA_ARGS__);
#define KN_CORE_CRITICAL(...)	Kanto::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define KN_TRACE(...)		Kanto::Log::GetClientLogger()->trace(__VA_ARGS__);
#define KN_INFO(...)		Kanto::Log::GetClientLogger()->info(__VA_ARGS__);
#define KN_WARN(...)		Kanto::Log::GetClientLogger()->warn(__VA_ARGS__);
#define KN_ERROR(...)		Kanto::Log::GetClientLogger()->error(__VA_ARGS__);
#define KN_CRITICAL(...)	Kanto::Log::GetClientLogger()->critical(__VA_ARGS__);