#pragma once

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "immapp/runner.h"
#include "pch.hpp"

#include "render/prim.hpp"
#include "render/prim_coolection.hpp"

namespace mr {
  class Application {
    private:
      bool show_window1 = true;
      bool show_window2 = false;

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

      ImVec2 scaled_mouse_pos() const noexcept
      {
        auto& io = ImGui::GetIO();
        ImVec2 mouse_pos = ImGui::GetMousePos();
        auto r = ImVec2(
            mouse_pos.x * io.DisplayFramebufferScale.x,
            mouse_pos.y * io.DisplayFramebufferScale.y);
        return r;
      }

    public:
      Application() noexcept;

      ~Application() noexcept = default;

      void input() noexcept {
        ImVec2 display_size = scaled_display_size();
        ImVec2 mouse_pos = scaled_mouse_pos();
        mouse_pos.x =  (2 * (mouse_pos.x / display_size.x) - 1);
        mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);

        auto& io = ImGui::GetIO();

        /*
           if (ImGui::IsKeyDown(ImGuiKey('S'))) {
           }
           */

        if (ImGui::IsMouseDown(0)) /* LMB */ {
          prims.emplace_back(mr::create_circle(mouse_pos.x, mouse_pos.y, 0.01));
        }
      }

      void render() noexcept {
        ImVec2 display_size = scaled_display_size();
        ImVec2 mouse_pos = scaled_mouse_pos();
        prims.back().posx() =  (2 * (mouse_pos.x / display_size.x) - 1);
        prims.back().posy() = -(2 * (mouse_pos.y / display_size.y) - 1);

        input();

        glViewport(0, 0, (GLsizei)display_size.x, (GLsizei)display_size.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        prims.draw();
      }

      void gui() noexcept;

      void run() noexcept {
        ImmApp::Run(runner_params, addons_params);
      }
  };
} // namespace mr
