#include <filesystem>
#include "pch.hpp"

#include "app/app.hpp"
#include "window/window.hpp"
#include "render/shader.hpp"
#include "render/vao.hpp"

void processInput(GLFWwindow *window);

int main(int argc, char **argv)
{
  glb::exec_path = std::filesystem::absolute(argv[0]).parent_path();

  mr::Application app;
  mr::Window *window = app.create_window(800, 600, "CGSGFOREVER");
  mr::Shader shader = mr::Shader("shaders/default");

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  mr::VAO vao = mr::VAO(std::span<float>{vertices}, std::span<unsigned int>{indices});

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window->handle())) {
    processInput(window->handle());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window->handle());
    glfwPollEvents();
  }

  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
