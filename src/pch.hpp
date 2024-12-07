#pragma once

#include <filesystem>
#include <iostream>
#include <span>
#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <httplib/httplib.h>
#include <glad/glad.h>
#include <nlohmann/json.hpp>

#include "rnd/timer.hpp"

namespace glb {
  inline std::filesystem::path exec_path;
  inline mr::Timer<float> timer;
} // namespace glb
