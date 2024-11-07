# my-paint
Simple canvas sharing program

## Dependencies
- ImGUI Bundle
- OpenGL

OpenGL is a part of your GPU driver so no need to install it. <br>
ImGUI Bundle is installed (if not found) via [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) in 'cmake/deps.cmake' file.

## Build instructions
```bash
  git clone https://github.com/2b1g1c/my-paint
  cd my-paint
  cmake -S . -B build # -G Ninja
  cmake --build build
```
Build files will be written to './build' directory

## Development
Gui elements should be placed inside mr::Application::gui function <br>
Render should be placed inside mr::Application::render function
Input handling should be placed inside mr::Application::input function
