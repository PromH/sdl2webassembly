# SDL2 WebAssembly Framework
A framework for writing SLD2 applications in C++ then compiling them as HTML/WebAssembly applications.

## Setup

Clone the repository with the following command:

```
git clone https://github.com/PromH/sdl2webassembly.git
```

### Common Dependencies

- [`emscripten`](https://emscripten.org/index.html) is a compiler for converting C/C++ code into code that can run in the browser (NodeJS, WebAssembly, etc).
- [`make`](https://www.gnu.org/software/make/) is a tool for generating executables and other non source files from source files.
- [NodeJS](https://nodejs.org/en/download) is an open-source, cross-platform JavaScript runtime environment.
- [`http-server`](https://www.npmjs.com/package/http-server) provides a simple way to host a HTTP server for serving resources. Required for handling `file://` XHR requests. See the quote from [Emscripten](https://emscripten.org/docs/getting_started/Tutorial.html):
  > Unfortunately several browsers (including Chrome, Safari, and Internet Explorer) do not support file:// XHR requests, and can’t load extra files needed by the HTML (like a .wasm file, or packaged file data as mentioned lower down). For these browsers you’ll need to serve the files using a local webserver and then open http://localhost:8000/hello.html).

### OS Specific Setup
Follow the setup instructions below for the appropriate operating system.

#### Windows (NOT WORKING - Makefile needs to be updated!)

1. Install [`chocolatey`](https://chocolatey.org/install)
    - [chocolatey](https://chocolatey.org/why-chocolatey) is a package manager for Windows.
2. Run `choco install sudo make emscripten`
3. Install [NodeJS](https://nodejs.org/en/download)
4. Run `npm install -g http-server`
    
#### Linux (Using [`WSL2`](https://learn.microsoft.com/en-us/windows/wsl/install))

1. [Install NodeJS](https://nodejs.org/en/download/package-manager)
2. Install `http-server`
    ```sh
    npm install -g http-server
    ```
3. Install Emscripten with the following commands (outside of this repo):
    ```sh
    git clone https://github.com/emscripten-core/emsdk.git
    ./emsdk/emsdk install latest
    ./emsdk/emsdk activate latest
    echo 'source "./emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
    source ./emsdk/emsdk_env.sh
    ```

### Optional Steps

If VS Code is being used, modify the _c_cpp_properties.json_ file to include the `emsdk` as an include path.

**Note:** To obtain the path, compile a C/C++ file with `emcc` and use the `-v` flag to get the paths.

## Running

1. `cd` to this repository.

1. Compile the game with the following command:
    ```sh
    make game
    ```
    It might fail to fully compile due to it downloading and setting up some ports for Emscripten. If that's the case run the following command to clean the files then rerun the above command:
    ```sh
    make clean
    make game
    ```
2. Start a server to host the generated HTML files:
    ```sh
    make serve
    ```
3. Vist the following URL and move the character with the WASD controls: http://127.0.0.1:8080/game.cc.html

## Vendor Dependencies
- [`skypjack/entt`](https://github.com/skypjack/entt) - For entity-component-system (ECS) management.
- [`gabime/spdlog`](https://github.com/gabime/spdlog) - For fast logging.
- [`Rookfighter/inifile-cpp`](https://github.com/Rookfighter/inifile-cpp) - For configuration parsing. 

## Extra Resources

- https://www.jamesfmackenzie.com/2019/11/30/whats-is-webassembly-hello-world/

## Further Plans

- Setup Premake
- Setup CMake
- Setup Tauri (or Electron)
- Setup pipelines
- Lefthooks
- Linting / Formatting
- Building to images
