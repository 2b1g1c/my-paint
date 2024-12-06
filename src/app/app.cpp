#include <cmath>

#include <thread>
#include "app.hpp"

void APIENTRY glDebugOutput(std::uint32_t source, std::uint32_t type,
                            std::uint32_t id, std::uint32_t severity,
                            int length, const char *message,
                            const void *userparam);

mr::Application::Application() noexcept
{
  _thread = std::jthread([this]() { _server.server_func(); });

  _runner_params.fpsIdling.enableIdling =
    false; // disable idling so that the shader runs at full speed
  _runner_params.appWindowParams.windowGeometry.size = {4'000, 2'000};
  _runner_params.appWindowParams.windowTitle = "CGSGFOREVER";
  // Do not create a default ImGui window, so that the shader occupies the whole display
  _runner_params.imGuiWindowParams.defaultImGuiWindowType =
    HelloImGui::DefaultImGuiWindowType::NoDefaultWindow;
  // PostInit is called after the ImGui context is created, and after OpenGL is initialized
  _runner_params.callbacks.PostInit = [&]() {
    glEnable(GL_SCISSOR_TEST);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, NULL);
  };
  _runner_params.callbacks.ShowGui = [&]() {
    ImGui::StyleColorsLight();
    gui();
  }; // ShowGui is called every frame, and is used to display the ImGui widgets
  _runner_params.callbacks.CustomBackground = [&]() {
    render();
  }; // CustomBackground is called every frame, and is used to display the custom background
  _addons_params.withMarkdown = true;
}

void mr::Application::gui() noexcept
{
  static float my_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::Button("Painting")) {
      if (_show_painting_window == true) {
        _show_painting_window = false;
      }
      else {
        _show_painting_window = true;
      }
    }
    ImGui::SetCursorPos({76, 0});

    if (ImGui::Button("Shapes")) {
      if (_show_shapes_window == true) {
        _show_shapes_window = false;
      }
      else {
        _show_shapes_window = true;
      }
    }
    ImGui::SetCursorPos({140, 0});

    if (ImGui::Button("Server")) {
      if (_show_server_window == true) {
        _show_server_window = false;
      }
      else {
        _show_server_window = true;
      }
    }
    ImGui::SetCursorPos({195, 0});

    if (ImGui::Button("Debug")) {
      if (_show_debug_window == true) {
        _show_debug_window = false;
      }
      else {
        _show_debug_window = true;
      }
    }
    ImGui::EndMainMenuBar();
  }


  if (_show_shapes_window) {
    ImGui::Begin("Shapes", &_show_shapes_window);

    if (ImGui::Button("Circle")) {
      ImVec2 display_size = scaled_display_size();
      ImVec2 mouse_pos = scaled_mouse_pos();
      mouse_pos.x = (2 * (mouse_pos.x / display_size.x) - 1);
      mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);
      _prims.emplace_back_synced(*this, mr::Prim::PrimType::eCircle, {mouse_pos.x, mouse_pos.y, _shape_size});
    }
    ImGui::SameLine();

    if (ImGui::Button("Square")) {
      ImVec2 display_size = scaled_display_size();
      ImVec2 mouse_pos = scaled_mouse_pos();
      mouse_pos.x = (2 * (mouse_pos.x / display_size.x) - 1);
      mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);
      _prims.emplace_back_synced(*this, mr::Prim::PrimType::eSquare, {mouse_pos.x, mouse_pos.y, _shape_size});
    }

    ImGui::End();
  }


  if (_show_painting_window) {
    ImGui::Begin("Painting parametrs", &_show_painting_window);
    //TODO: add painting checkbox which turns off and on brush

    ImGui::ColorEdit4("Change color", my_color);
    ImGui::SliderFloat("Size", &_shape_size, 0.0f, 1.0f, "%.2f");

    ImGui::End();
  }

  if (_show_server_window) {
    ImGui::Begin("Server menu", &_show_server_window);
    if (ImGui::Button("Join server")) {
      //show_host_window = false;
      _show_join_window = true;
      _show_server_window = false;
    }
    ImGui::End();
  }

  if (_show_join_window) {
    ImGui::Begin("Join to local server", &_show_join_window);

    static char ip_address[20] = "127.0.0.1";
    ImGui::InputText("IP Address", ip_address, 20);

    if (ImGui::Button("Connect")) {
      std::cout << "Connecting to: " << ip_address << std::endl;
      //add connecting func
    }

    ImGui::End();
  }

  if (_show_debug_window) {
    ImGui::Begin("Debug menu", &_show_debug_window);

    ImGui::Text("FPS: %.1f", HelloImGui::FrameRate());

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
