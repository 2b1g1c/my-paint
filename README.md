# my-paint
Simple canvas sharing program

## Dependencies
- ImGUI Bundle
- OpenGL
- GLFW3
- Intel TBB (on GCC and Clang only)

OpenGL is a part of your GPU driver so no need to install it. <br>
GLFW3 is a OS-abstraction library, needs to be installed globally. <br>
Intel TBB is a threading library. It is required by GCC/Clang for use of `std::execution`. <br>
ImGUI Bundle is installed (if not found) via [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) in 'cmake/deps.cmake' file.

#### Note on CPM.cmake
  All dependencies installed via CPM.cmake are inside build directory by default.
  If you remove this directory, all dependencies need to be installed again.
  To avoid this put `export CPM_SOURCE_CACHE=$HOME/.cache/CPM` in your `.bashrc`

## Build instructions
```bash
  git clone https://github.com/2b1g1c/my-paint
  cd my-paint
  cmake -S . -B build # -G Ninja
  cmake --build build
```
Build files will be written to './build' directory

## Development
Gui elements should be placed inside `mr::Application::gui` function <br>
Render should be placed inside `mr::Application::render` function
Input handling should be placed inside `mr::Application::input` function
