#pragma once

#include "pch.hpp"
#include "window/window.hpp"

namespace mr {
  class Application {
  private:
    std::vector<Window> _windows;
    bool is_glad_inited = false;

  public:
    Application() noexcept {
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

      // to make sure no reallocation will be present
      _windows.reserve(100);
    }

    Window* create_window(int width, int height, std::string_view handle) {
      _windows.emplace_back(width, height, handle);
      if (!is_glad_inited) {
        is_glad_inited = true;
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
          std::cout << "Failed to initialize GLAD" << std::endl;
          exit(30);
        }
      }
      return _windows.data() + _windows.size() - 1;
    }

    ~Application() noexcept {
      glfwTerminate();
    }
  };
}
