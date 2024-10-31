#include <filesystem>
#include "pch.hpp"

#include "app/app.hpp"
#include "window/window.hpp"
#include "render/shader.hpp"
#include "render/prim.hpp"

void processInput(GLFWwindow *window, mr::Prim &pr);

int main(int argc, char **argv)
{
  glb::exec_path = std::filesystem::absolute(argv[0]).parent_path();

  mr::Application app;
  mr::Window *window = app.create_window(800, 600, "CGSGFOREVER");

  using vec = float[2];
  vec vertices[] = {
    {0.5f,  0.5f},  // top right
    {0.5f, -0.5f},  // bottom right
    {-0.5f, -0.5f}, // bottom left
    {-0.5f,  0.5f}  // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  mr::Prim prim("default", std::span<vec>{vertices}, std::span<unsigned int>{indices}, 0.0f, 0.0f, 1.0f);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window->handle())) {
    processInput(window->handle(), prim);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    prim.draw();

    glfwSwapBuffers(window->handle());
    glfwPollEvents();
  }

  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, mr::Prim &pr)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
           glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
	pr.posx() -= 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
           glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
	pr.posx() += 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
           glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
	pr.posy() -= 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
           glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
	pr.posy() += 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    pr.rot() += 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    pr.rot() -= 0.001;
  }
}
