#pragma once

#include "imgui.h"
#include "immapp/runner.h"
#include "pch.hpp"

#include "rnd/prim.hpp"
#include "rnd/prim_coolection.hpp"
#include "srv/server.hpp"

namespace mr {
  class Prim;

  class Application {
  private:
    friend class Server;

    HelloImGui::RunnerParams _runner_params;
    ImmApp::AddOnsParams _addons_params;
    mr::PrimCollection _prims;
    mr::Server _server = {*this, get_self_ip()};
    std::jthread _thread;

    mr::Prim::PrimType _ptype = mr::Prim::PrimType::eSquare;
    bool _show_shapes_window = false;
    bool _show_painting_window = false;
    bool _show_server_window = false;
    bool _show_debug_window = false;
    bool _show_join_window = false;
    float _shape_size = 0.01f; //drawing size

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
      auto r = ImVec2(mouse_pos.x * io.DisplayFramebufferScale.x,
                      mouse_pos.y * io.DisplayFramebufferScale.y);
      return r;
    }

  public:
    Application() noexcept;

    ~Application() noexcept
    {
      _server.stop();
      _thread.request_stop();
    }

    void input() noexcept
    {
      ImVec2 display_size = scaled_display_size();
      ImVec2 mouse_pos = scaled_mouse_pos();
      mouse_pos.x = (2 * (mouse_pos.x / display_size.x) - 1);
      mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);

      auto& io = ImGui::GetIO();

      if (ImGui::IsMouseDown(0)) /* LMB */ {
        _prims.emplace_back_synced(*this, _ptype, {mouse_pos.x, mouse_pos.y, _shape_size});
      }
    }

    void render() noexcept
    {
      static Shader shader = Shader("default");

      ImVec2 display_size = scaled_display_size();
      ImVec2 mouse_pos = scaled_mouse_pos();
      // _prims.back().posx() =  (2 * (mouse_pos.x / display_size.x) - 1);
      // _prims.back().posy() = -(2 * (mouse_pos.y / display_size.y) - 1);

      input();

      glViewport(0, 0, (GLsizei)display_size.x, (GLsizei)display_size.y);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.apply();
      _prims.draw();
    }

    void gui() noexcept;

    void run() noexcept { ImmApp::Run(_runner_params, _addons_params); }

    void sync_object(std::string other) { _server.sync_object(other); }

    void connect_to_canvas(const std::string& str) noexcept
    {
      _server.connect_to_canvas(str);
    }
  };
} // namespace mr
