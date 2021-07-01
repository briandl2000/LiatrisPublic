#pragma once

#include "Liatris/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Liatris {
	class Log
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

// Core log macros
#define LIA_CORE_TRACE(...) ::Liatris::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LIA_CORE_INFO(...)  ::Liatris::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LIA_CORE_WARN(...)  ::Liatris::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LIA_CORE_ERROR(...) ::Liatris::Log::GetCoreLogger()->error(__VA_ARGS__)

// Core log macros
#define LIA_TRACE(...) ::Liatris::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LIA_INFO(...)  ::Liatris::Log::GetClientLogger()->info(__VA_ARGS__)
#define LIA_WARN(...)  ::Liatris::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LIA_ERROR(...) ::Liatris::Log::GetClientLogger()->error(__VA_ARGS__)
