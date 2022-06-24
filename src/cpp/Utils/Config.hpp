#pragma once
#include <spdlog/spdlog.h>

struct ConfigData {
  spdlog::level::level_enum logLevel = spdlog::level::info;

  void ParseConfigFile(const char* file);
};
