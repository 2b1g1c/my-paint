#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <span>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/timer.hpp"

namespace glb {
  inline std::filesystem::path exec_path;
  inline mr::Timer<float> timer;
}
