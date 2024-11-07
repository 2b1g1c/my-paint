#pragma once

#include "pch.hpp"

namespace mr {
  class Window {
    private:
      GLFWwindow* _handle = nullptr;

    public:
      Window() noexcept = default;
      Window(int width, int height, std::string_view handle) noexcept;

      // getters
      GLFWwindow* handle() noexcept { return _handle; }
  };
} // namespace mr
