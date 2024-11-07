#include <filesystem>
#include <functional>
#include "pch.hpp"

#include "app/app.hpp"
#include "window/window.hpp"
#include "render/prim.hpp"
#include "render/prim_coolection.hpp"
#include "render/timer.hpp"

void processInput(GLFWwindow *window, mr::PrimCollection &prims, mr::Prim &pr);

int main(int argc, char **argv) {
  glb::exec_path = std::filesystem::absolute(argv[0]).parent_path();
  glb::timer = mr::Timer<float>{};

  mr::Application app;
  mr::Window *window = app.create_window(800, 600, "CGSGFOREVER");

  mr::PrimCollection prims;
  mr::Prim active_prim = mr::create_square(0.0, 0.0, 0.1);

  active_prim = mr::create_square(0.2, 0.2, 0.1);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window->handle())) {
    processInput(window->handle(), prims, active_prim);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    prims.draw();
    active_prim.draw();

    glfwSwapBuffers(window->handle());
    glfwPollEvents();
  }

  return 0;
}

void processMouse(GLFWwindow* window, mr::PrimCollection &prims, mr::Prim &active_prim) {
  static bool pressed = false;

  double posx, posy;
  glfwGetCursorPos(window, &posx, &posy);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  posx =   (posx / width) * 2 - 1;
  posy = -((posy / height) * 2 - 1);
  active_prim.posx() = posx;
  active_prim.posy() = posy;

  if (!pressed && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    pressed = true;
  }
  if (pressed && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
    prims.add(std::move(active_prim));
    if (prims.size() % 2 == 0) {
      active_prim = mr::create_circle(posx, posy, 0.1);
    }
    else {
      active_prim = mr::create_square(posx, posy, 0.1);
    }

    pressed = false;
  }
}

void processInput(GLFWwindow *window, mr::PrimCollection &prims, mr::Prim &active_prim) {
  processMouse(window, prims, active_prim);

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
      glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    active_prim.posx() -= 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
      glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    active_prim.posx() += 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
      glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    active_prim.posy() -= 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
      glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    active_prim.posy() += 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    active_prim.rot() += 0.001;
  }
  else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    active_prim.rot() -= 0.001;
  }
}

