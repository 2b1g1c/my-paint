#include <cmath>

#include "app.hpp"

mr::Application::Application() noexcept {
  runner_params.fpsIdling.enableIdling = false; // disable idling so that the shader runs at full speed
  runner_params.appWindowParams.windowGeometry.size = {4000, 2000};
  runner_params.appWindowParams.windowTitle = "CGSGFOREVER";
  runner_params.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::NoDefaultWindow; // Do not create a default ImGui window, so that the shader occupies the whole display
                                                                                                                // PostInit is called after the ImGui context is created, and after OpenGL is initialized
  runner_params.callbacks.PostInit = [&]() {
    glEnable(GL_SCISSOR_TEST);
    glClearColor(1, 1, 1, 1);
    prims.emplace_back(mr::create_circle(0.2, 0.2, 0.01));
  };
  runner_params.callbacks.ShowGui = [&]() { gui(); }; // ShowGui is called every frame, and is used to display the ImGui widgets
  runner_params.callbacks.CustomBackground = [&]() { render(); }; // CustomBackground is called every frame, and is used to display the custom background
  addons_params.withMarkdown = true;
}

void mr::Application::gui() noexcept {
  static float my_color[4] = {0.0f, 1.0f, 0.0f, 1.0f};
  if (this->show_window1) {
    ImGui::Begin("Are u host?", &this->show_window1);
    if (ImGui::Button("Yes")) {
      this->show_window1 = false;
      this->show_window2 = true;
    }
    ImGui::End();
  }

  if (this->show_window2) {
    ImVec2 display_size = scaled_display_size();
    ImVec2 mouse_pos = scaled_mouse_pos();
    mouse_pos.x =  (2 * (mouse_pos.x / display_size.x) - 1);
    mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);
    ImGui::Begin("Tools", &this->show_window2, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open..")) {
          /* Do stuff */
        }
        if (ImGui::MenuItem("Save")) {
          /* Do stuff */
        }
        if (ImGui::MenuItem("Close")) {
          this->show_window2 = false;
          ImGui::End();
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();

      if (ImGui::CollapsingHeader("Colour")) {
        ImGui::ColorEdit4("Color", my_color);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(my_color[0], my_color[1], my_color[2], my_color[3]));
        ImGui::PopStyleColor();
        float samples[100];
        for (int n = 0; n < 100; n++) {
          samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
        }
        ImGui::PlotLines("Samples", samples, 100);
      }
      if (ImGui::CollapsingHeader("Drawing materials")) {
        if (ImGui::Button("Circle")) {
          prims.emplace_back(mr::create_circle(mouse_pos.x, mouse_pos.y, 0.01));
        }
        if (ImGui::Button("Square")) {
          prims.emplace_back(mr::create_square(mouse_pos.x, mouse_pos.y, 0.01));
        }
        if (ImGui::Button("Ellipse")) {
          prims.emplace_back(mr::create_square(mouse_pos.x, mouse_pos.y, 0.04));
        }
      }
    }

    ImGui::End();
  }
}

void APIENTRY glDebugOutput(std::uint32_t source, std::uint32_t type,
                            std::uint32_t id, std::uint32_t severity,
                            int length, const char *message,
                            const void *userparam)
{
  int len = 0;
  static char Buf[10'000];

  len += sprintf(Buf + len, "Debug message (%i) %s\n", id, message);
  switch (source) {
    case GL_DEBUG_SOURCE_API:
      len += sprintf(Buf + len, "Source: API\n");
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      len += sprintf(Buf + len, "Source: Window System\n");
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      len += sprintf(Buf + len, "Source: Shader Compiler\n");
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      len += sprintf(Buf + len, "Source: Third Party\n");
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      len += sprintf(Buf + len, "Source: Application");
      break;
    case GL_DEBUG_SOURCE_OTHER:
      len += sprintf(Buf + len, "Source: Other");
      break;
  }
  len += sprintf(Buf + len, "\n");

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      len += sprintf(Buf + len, "Type: Error");
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      len += sprintf(Buf + len, "Type: Deprecated Behaviour");
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      len += sprintf(Buf + len, "Type: Undefined Behaviour");
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      len += sprintf(Buf + len, "Type: Portability");
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      len += sprintf(Buf + len, "Type: Performance");
      break;
    case GL_DEBUG_TYPE_MARKER:
      len += sprintf(Buf + len, "Type: Marker");
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      len += sprintf(Buf + len, "Type: Push Group");
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      len += sprintf(Buf + len, "Type: Pop Group");
      break;
    case GL_DEBUG_TYPE_OTHER:
      len += sprintf(Buf + len, "Type: Other");
      break;
  }
  len += sprintf(Buf + len, "\n");

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      len += sprintf(Buf + len, "Severity: high");
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      len += sprintf(Buf + len, "Severity: medium");
      break;
    case GL_DEBUG_SEVERITY_LOW:
      len += sprintf(Buf + len, "Severity: low");
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      len += sprintf(Buf + len, "Severity: notification");
      break;
  }
  len += sprintf(Buf + len, "\n\n");

  std::cout << Buf;
} /* End of 'glDebugOutput' function */
