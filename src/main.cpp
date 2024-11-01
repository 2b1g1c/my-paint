#include <filesystem>
#include "pch.hpp"

#include "app/app.hpp"
#include "window/window.hpp"
#include "render/prim.hpp"
#include "render/prim_coolection.hpp"

void processInput(GLFWwindow *window, mr::Prim &pr);

int main(int argc, char **argv) {
  glb::exec_path = std::filesystem::absolute(argv[0]).parent_path();

  mr::Application app;
  mr::Window *window = app.create_window(800, 600, "CGSGFOREVER");

  mr::PrimCollection prims;
  prims.add(mr::PrimCollection::PrimType::eCircle, mr::create_circle(0, 0.1, 0.1));
  prims.add(mr::PrimCollection::PrimType::eCircle, mr::create_circle(0, 0, 0.1));
  prims.add(mr::PrimCollection::PrimType::eSquare, mr::create_square(0, 0.1, 0.1));
  prims.add(mr::PrimCollection::PrimType::eSquare, mr::create_square(0, 0, 0.1));

  mr::Prim active_prim = mr::create_circle(0, 0, 0.1);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window->handle())) {
    processInput(window->handle(), active_prim);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    prims.draw();
    active_prim.draw();

    glfwSwapBuffers(window->handle());
    glfwPollEvents();
  }

  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, mr::Prim &pr)
{
  double posx, posy;
  glfwGetCursorPos(window, &posx, &posy);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  pr.posx() =   (posx / width) * 2 - 1;
  pr.posy() = -((posy / height) * 2 - 1);

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
