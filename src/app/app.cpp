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
  static float my_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  

  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::Button("Painting")) {
        if (show_painting_window == true) {
        show_painting_window = false;
        }
        else {
          show_painting_window = true;
        }
    }
    ImGui::SetCursorPos({76, 0});

    if (ImGui::Button("Shapes")) {
      if (show_shapes_window == true) {
        show_shapes_window = false;
      }
      else {
        show_shapes_window = true;
      }
    }
    ImGui::SetCursorPos({140, 0});

    if (ImGui::Button("Server")) {
      if (show_server_window == true) {
        show_server_window = false;
      }
      else {
        show_server_window = true;
      }
    }
    ImGui::SetCursorPos({195, 0});

    if (ImGui::Button("Debug")) {
      if (show_debug_window == true) {
        show_debug_window = false;
      }
      else {
        show_debug_window = true;
      }
    }
    ImGui::EndMainMenuBar();
  }


  if (show_shapes_window) {
    ImGui::Begin("Shapes", &show_shapes_window); 

    if (ImGui::Button("Circle")) {
      ImVec2 display_size = scaled_display_size();
      ImVec2 mouse_pos = scaled_mouse_pos();
      mouse_pos.x = (2 * (mouse_pos.x / display_size.x) - 1);
      mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);
      prims.emplace_back(mr::create_circle(mouse_pos.x, mouse_pos.y, size));
    }
    ImGui::SameLine();

    if (ImGui::Button("Square")) {
      ImVec2 display_size = scaled_display_size();
      ImVec2 mouse_pos = scaled_mouse_pos();
      mouse_pos.x = (2 * (mouse_pos.x / display_size.x) - 1);
      mouse_pos.y = -(2 * (mouse_pos.y / display_size.y) - 1);
      prims.emplace_back(mr::create_square(mouse_pos.x, mouse_pos.y, size));
    }

    ImGui::End();
  }

  
  if (show_painting_window) {
    ImGui::Begin("Painting parametrs", &show_painting_window);
    //TODO: add painting checkbox which turns off and on brush
    
    ImGui::ColorEdit4("Change color", my_color); //цвет рисования и фигур!!!!!
    ImGui::SliderFloat("Size", &size, 0.0f, 1.0f, "%.2f"); 


    ImGui::End();
  }

  if (show_server_window) {
    ImGui::Begin("Server menu", &show_server_window);
    if (ImGui::Button("Join server")) {
      //show_host_window = false;
      show_join_window = true;
      show_server_window = false;
    }
    /* 
    f (ImGui::Button("Сreate server")) {
      show_host_window = true;
      show_join_window = false;
      show_server_window = false;
    }
    */
    ImGui::End(); 
    
  }
   /*
   if (show_host_window) {
    ImGui::Begin("Local server hosting is in progress...", &show_host_window);

    ImGui::Text("Nothing! Add server creating process");

    ImGui::End();
  }
  */
  if (show_join_window) {
    ImGui::Begin("Join to local server", &show_join_window);

    static char ip_address[20] = "127.0.0.1"; 
    ImGui::InputText("IP Address", ip_address, 20); 

    if (ImGui::Button("Connect")) {

      std::cout << "Connecting to: " << ip_address << std::endl;
      //add connecting func

    }

    ImGui::End();
  }

  if (show_debug_window) {
    ImGui::Begin("Debug menu", &show_debug_window);

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
