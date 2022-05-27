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
EMCC_FLAGS = --preload-file $(ASSETDIR) --use-preload-plugins
EMCC_PORTS = -s USE_LIBPNG=1 -s USE_ZLIB=1 -s USE_SDL_IMAGE=2 -s USE_SDL=2
CCFLAGS = -std=c++1z $(INCLUDES) $(EMCC_PORTS) $(EMCC_FLAGS)

SRC_DIR := src/cpp
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

HDR_DIR := src/cpp
HDR_FILES := $(wildcard $(HDR_DIR)/*.hpp) $(wildcard $(HDR_DIR)/*.h) 

OBJ_DIR := obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

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

help:	## Show this help.
	@echo help

sdl-example:	## Compiles the SDL application into a webassembly application.
	$(CC) examples/$(example_sdl_target_file).cpp -o $(appname).cc.js -o $(appname).cc.html

sdl2-example:	## Compiles the SDL2 application into a webassembly application.
	$(CC) -c examples/$(example_sdl2_target_file).cpp -o $(example_sdl2_target_file).o $(CCFLAGS)
	$(CC) $(example_sdl2_target_file).o -o $(appname).cc.js -o $(appname).cc.html $(CCFLAGS)

$(OBJ_DIR):	## Generates a directory for holding object files.
	mkdir $(OBJ_DIR)

$(OBJ_FILES): | $(OBJ_DIR)	## Makes the object directory a dependency for object files.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR_FILES)	## Compiles all cpp files located in the src directory.
	$(CC) -c -o $@ $< $(CCFLAGS)

game: $(OBJ_FILES)	## Compiles the main game into a webassembly application.
	$(CC) -o $@.cc.js -o $@.cc.html $^ $(CCFLAGS)
