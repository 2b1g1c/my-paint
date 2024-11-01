#pragma once

#include "pch.hpp"
#include "window/window.hpp"

namespace mr {
  class Application {
  private:
    std::vector<Window> _windows;
    bool is_glad_inited = false;

  public:
    Application() noexcept;

    Window* create_window(int width, int height, std::string_view handle);

    ~Application() noexcept {
      glfwTerminate();
    }
  };
}
