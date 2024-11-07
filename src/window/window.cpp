#include "window/window.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

mr::Window::Window(int width, int height, std::string_view handle) noexcept
{
  _handle = glfwCreateWindow(width, height, handle.data(), NULL, NULL);
  if (_handle == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(47);
  }

  glfwMakeContextCurrent(_handle);
  glfwSetFramebufferSizeCallback(_handle, framebuffer_size_callback);
}
