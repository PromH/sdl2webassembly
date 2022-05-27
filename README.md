## Setup instructions for windows
* Install `chocolatey`
* Run `choco install sudo make emscripten`
* Run `npm install -g http-server`

### Optional Steps
If VS Code is being used, modify the *c_cpp_properties.json* file to include the `emsdk` as an include path.

**Note:** To obtain the path, compile a C/C++ file with `emcc` and use the `-v` flag to get the paths.


## Further Plans

* Setup Premake
* Setup CMake
* Setup Tauri (or Electron)
* Setup pipelines
* Lefthooks
* Linting / Formatting
* Building to images

