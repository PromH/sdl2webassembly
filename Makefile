## ----------------------------------------------------------------------
## This is a Windows Makefile for compiling a SDL2 application with
## EMScripten.
## ----------------------------------------------------------------------

# Environment Variables
DETECTED_OS =
RM =
RMDIR = 
ASSETDIR = src/assets
CC = emcc
INCLUDES = -Ivendor
EMCC_FLAGS = --preload-file $(ASSETDIR) --use-preload-plugins -sNO_DISABLE_EXCEPTION_CATCHING
EMCC_PORTS = -s USE_LIBPNG=1 -s USE_ZLIB=1 -s USE_SDL_IMAGE=2 -s USE_SDL=2
CCFLAGS = -std=c++1z $(INCLUDES) $(EMCC_PORTS) $(EMCC_FLAGS)

SRC_DIR := src/cpp
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')

HDR_DIR := src/cpp
HDR_FILES := $(shell find $(HDR_DIR) -name '*.hpp') $(shell find $(HDR_DIR) -name '*.h')

OBJ_DIR := obj
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:%.cpp=%.o))

appname = example
example_sdl_target_file = hello_world_sdl
example_sdl2_target_file = hello_world_sdl2

# OS Configurations
ifeq ($(OS),Windows_NT) 
    DETECTED_OS := Windows
		RM = del /Q /F
		RMDIR = RMDIR /S /Q
else
    DETECTED_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
		RM = rm -f
		RMDIR = rm -rf 
endif

# Commands
clean:	## Removes all files generated from this Makefile.
	$(RM) *.o *.cc.wasm *.cc.js *.cc.html *.cc.data
	$(RMDIR) obj

.PHONY: all clean

all: $(OBJ_FILES)

help:                       ## Show this help.
	@sed -ne '/@sed/!s/## //p' $(MAKEFILE_LIST)

prepare-env:                ## Prepares the development environment.
	@sudo cp tools/bin/clang-format-14_linux-amd64 /usr/local/bin/clang-format
	@sudo chmod +x /usr/local/bin/clang-format

format:                     ## Formats all the C++ files in the source directory.
	./tools/scripts/format.sh

sdl-example:                ## Compiles the SDL application into a webassembly application.
	$(CC) examples/$(example_sdl_target_file).cpp -o $(appname).cc.js -o $(appname).cc.html

sdl2-example:               ## Compiles the SDL2 application into a webassembly application.
	$(CC) -c examples/$(example_sdl2_target_file).cpp -o $(example_sdl2_target_file).o $(CCFLAGS)
	$(CC) $(example_sdl2_target_file).o -o $(appname).cc.js -o $(appname).cc.html $(CCFLAGS)

$(OBJ_DIR):                 # Generates a directory for holding object files.
	@echo Generating mirror directory for object files.
	mkdir $(OBJ_DIR)
	find $(SRC_DIR) -type d -exec mkdir -p $(OBJ_DIR)/'{}' \;

$(OBJ_FILES): | $(OBJ_DIR)  # Makes the object directory a dependency for object files.

$(OBJ_DIR)/%.o: %.cpp       # Compiles all cpp files located in the src directory.
	@echo $(@)
	$(CC) $(CCFLAGS) -c $< -o $@

game: $(OBJ_FILES)          ## Compiles the main game into a webassembly application.
	$(CC) -o $@.cc.js -o $@.cc.html $^ $(CCFLAGS)

serve: game.cc.html         ## Starts a simple HTTP server to serve the application.
	npx http-server -c-1
