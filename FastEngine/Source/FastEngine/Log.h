#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

#include "spdlog/fmt/fmt.h"

namespace FastEngine
{
	class FE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


}

//Core log macros
#define FE_CORE_ERROR(...)   ::FastEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FE_CORE_WARN(...)    ::FastEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FE_CORE_LOG(...)     ::FastEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FE_CORE_TRACE(...)   ::FastEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FE_CORE_FATAL(...)   ::FastEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define FE_ERROR(...)   ::FastEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FE_WARN(...)    ::FastEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FE_LOG(...)     ::FastEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FE_TRACE(...)   ::FastEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FE_FATAL(...)   ::FastEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
