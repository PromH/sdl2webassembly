## Setup instructions for windows

- Install `chocolatey`
- Run `choco install sudo make emscripten`
- Run `npm install -g http-server`

### Optional Steps

If VS Code is being used, modify the _c_cpp_properties.json_ file to include the `emsdk` as an include path.

**Note:** To obtain the path, compile a C/C++ file with `emcc` and use the `-v` flag to get the paths.

## Vendor Dependencies
- [`skypjack/entt`](https://github.com/skypjack/entt) - For entity-component-system (ECS) management.
- [`gabime/spdlog`](https://github.com/gabime/spdlog) - For fast logging.
- [`Rookfighter/inifile-cpp`](https://github.com/Rookfighter/inifile-cpp) - For configuration parsing. 

## Further Plans

- Setup Premake
- Setup CMake
- Setup Tauri (or Electron)
- Setup pipelines
- Lefthooks
- Linting / Formatting
- Building to images
