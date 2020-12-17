#pragma once
#include <Kanto/Core.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Kanto
{
	class KANTO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define KN_CORE_TRACE(...)		Kanto::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define KN_CORE_INFO(...)		Kanto::Log::GetCoreLogger()->info(__VA_ARGS__);
#define KN_CORE_WARN(...)		Kanto::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define KN_CORE_ERROR(...)		Kanto::Log::GetCoreLogger()->error(__VA_ARGS__);
#define KN_CORE_FATAL(...)		Kanto::Log::GetCoreLogger()->fatal(__VA_ARGS__);

#define KN_TRACE(...)	Kanto::Log::GetClientLogger()->trace(__VA_ARGS__);
#define KN_INFO(...)		Kanto::Log::GetClientLogger()->info(__VA_ARGS__);
#define KN_WARN(...)		Kanto::Log::GetClientLogger()->warn(__VA_ARGS__);
#define KN_ERROR(...)	Kanto::Log::GetClientLogger()->error(__VA_ARGS__);
#define KN_FATAL(...)	Kanto::Log::GetClientLogger()->fatal(__VA_ARGS__);