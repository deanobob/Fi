# Makefile

# Returns 1 if Linux, else 0
IS_LINUX := $(shell uname -a | grep -c Linux)

# Define paths and library files
INC_PATH := -Isource/ -Isource/core/ -Isource/input/ -Isource/logger/ -Isource/utilities/ -I/usr/local/include/
LIB_PATH := -L/usr/local/lib
LIBS     := -lpthread #-lSDL2 -lallegro -lallegro_main -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf

# Define compiler
CXX := g++-10
ifeq ($(IS_LINUX), 1)
	CXX := g++
endif

# Compiler options
CXX_FLAGS := -std=c++17 -ggdb -Wall -Wextra -Wno-unused-parameter $(INC_PATH)
LD_FLAGS := $(LIB_PATH) $(LIBS)

# Name the executable here
EXECUTABLE_NAME := Malon

# GDB configuration
GDB_PORT := 6000

# Important folders
SRC    := source
BIN    := bin
ASSETS := assets
OBJ    := $(BIN)/obj

# Recursively find files
SOURCE_FILES := $(shell find source -name "*.cpp")

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

.PHONY: all build clean prepare run debug review

all: build

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@$(CXX) -o $@ $^ $(LD_FLAGS)
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) -c $(CXX_FLAGS) -o $@ $<

build: $(EXECUTABLE_FILES)

clean:
	rm -rf $(BIN)/*

prepare:
	@echo Preparing assets
	rm -rf $(BIN)/$(ASSETS)
	cp -r $(ASSETS) $(BIN)/

run: build prepare
	@echo Running $(EXECUTABLE_NAME)
	$(BIN)/$(EXECUTABLE_NAME)

debug: build prepare
	@echo Running $(EXECUTABLE_NAME) with GDB server on port $(GDB_PORT)
	gdbserver :$(GDB_PORT) $(BIN)/$(EXECUTABLE_NAME)

review:
	cppcheck .
