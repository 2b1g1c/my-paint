#include <filesystem>
#include <functional>
#include "pch.hpp"

#include "app/app.hpp"
#include "render/prim.hpp"
#include "render/prim_coolection.hpp"
#include "render/timer.hpp"

#include "immapp/immapp.h"
#include "imgui.h"

int main(int argc, char **argv)
{
  glb::exec_path = std::filesystem::absolute(argv[0]).parent_path();
  glb::timer = mr::Timer<float> {};

  auto app = mr::Application();
  app.run();
}
