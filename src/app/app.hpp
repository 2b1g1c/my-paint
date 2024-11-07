#pragma once

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "immapp/runner.h"
#include "pch.hpp"

#include "render/prim_coolection.hpp"

namespace mr {
  class Application {
    private:
      HelloImGui::RunnerParams runner_params;
      ImmApp::AddOnsParams addons_params;
      mr::PrimCollection prims;
      bool is_glad_inited = false;

      ImVec2 scaled_display_size() const noexcept
      {
        auto& io = ImGui::GetIO();
        auto r = ImVec2(io.DisplaySize.x * io.DisplayFramebufferScale.x,
            io.DisplaySize.y * io.DisplayFramebufferScale.y);
        return r;
      }

    public:
      Application() noexcept;

      ~Application() noexcept = default;

      void render() const noexcept {
        ImVec2 displaySize = scaled_display_size();
        glViewport(0, 0, (GLsizei)displaySize.x, (GLsizei)displaySize.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        prims.draw();
      }

      void gui() const noexcept {
        ImGui::Begin("Debug info");
        ImGui::Text("FPS: %.1f", HelloImGui::FrameRate());
        ImGui::End();
      }

      void run() noexcept {
        ImmApp::Run(runner_params, addons_params);
      }
  };
} // namespace mr
