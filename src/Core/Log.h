#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace SpikeSim {

  class Log
  {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
  };

}

#define SS_TRACE(...)     ::SpikeSim::Log::GetLogger()->trace(__VA_ARGS__)
#define SS_INFO(...)      ::SpikeSim::Log::GetLogger()->info(__VA_ARGS__)
#define SS_WARN(...)      ::SpikeSim::Log::GetLogger()->warn(__VA_ARGS__)
#define SS_ERROR(...)     ::SpikeSim::Log::GetLogger()->error(__VA_ARGS__)
#define SS_FATAL(...)     ::SpikeSim::Log::GetLogger()->fatal(__VA_ARGS__)
#define SS_ASSERT(x, ...) { if(!(x)) SS_ERROR("Assertion Failed: {0}", __VA_ARGS__); }
