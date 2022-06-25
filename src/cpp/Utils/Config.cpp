#include "Config.hpp"

#include <inifile-cpp/inicpp.h>
#include <spdlog/spdlog.h>

#include <string>

void ConfigData::ParseConfigFile(const char* file) {
  // Loading
  ini::IniFile myIni;
  myIni.load(file);

  // Updating object
  this->logLevel =
      spdlog::level::from_str(myIni["LOGGER"]["level"].as<const char*>());
}
