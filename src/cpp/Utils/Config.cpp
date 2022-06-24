#include <string>

#include <spdlog/spdlog.h>
#include <inifile-cpp/inicpp.h>

#include "Config.hpp"

void ConfigData::ParseConfigFile(const char* file) {
  // Loading
  ini::IniFile myIni;
  myIni.load(file);

  // Updating object
  this->logLevel = spdlog::level::from_str(myIni["LOGGER"]["level"].as<const char*>());
}
