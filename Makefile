# Makefile

# Returns 1 if Linux, else 0
IS_LINUX := $(shell uname -a | grep -c Linux)

# Define paths and library files
INC_PATH := -Isource/ \
			-Isource/console/ \
			-Isource/console/commands/ \
			-Isource/core/ \
			-Isource/core/components \
			-Isource/core/subsystems \
			-Isource/framework/ \
			-Isource/input/ \
		    -Isource/message/ \
			-Isource/render/ \
			-Isource/ui/ \
            -Isource/utilities/ \
			-Ithird_party/ \
			-I/usr/local/include/
LIB_PATH := -Llib/ \
            -L/usr/local/lib
LIBS := -lpthread #-lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
TEST_LIBS := -lpthread #-lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf

# Define compiler
CXX := g++-10

# Localise for OS
ifeq ($(IS_LINUX), 1)
	CXX := g++
else
	LIBS := $(LIBS) -lallegro_main
endif

# Compiler options
CXX_FLAGS := -std=c++17 -ggdb -Wall -Wextra -pedantic -Wconversion -Wno-unused-parameter -DCI $(INC_PATH)
LD_FLAGS := $(LIB_PATH) $(LIBS)
TEST_LD_FLAGS := $(LIB_PATH) $(TEST_LIBS)

# Name the executable here
EXECUTABLE_NAME := Malon
TEST_EXECUTABLE_NAME := Malon_test

# GDB configuration
GDB_PORT := 6000

# Important folders
BIN      := bin
LIB      := lib
ASSETS   := assets
OBJ      := obj
TEST_OBJ := $(OBJ)/test

# Recursively find files
SOURCE_FILES := $(shell find source/* -name "*.cpp" ! -name "*_test.cpp")
EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

# Recursively find test files (excluding main.cpp to avoid duplicate entry)
TEST_SOURCE_FILES := $(shell find * -name "*.cpp" ! -name "main.cpp")
TEST_EXECUTABLE_FILES = $(TEST_EXECUTABLE_NAME:%=$(BIN)/%)
TEST_OBJECT_FILES     = $(TEST_SOURCE_FILES:%.cpp=$(TEST_OBJ)/%.o)

.PHONY: all build clean prepare run debug test review

all: env build

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@echo "$(CXX) -o $@ $^ $(LD_FLAGS)"
	@$(CXX) -o $@ $^ $(LD_FLAGS)
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	@echo Compiling $<
	@echo "$(CXX) $(CXX_FLAGS) -c $< -o $@"
	@mkdir -p $(@D)
	@$(CXX) $(CXX_FLAGS) -c $< -o $@

$(TEST_EXECUTABLE_FILES): $(TEST_OBJECT_FILES)
	@$(CXX) -o $@ $^ $(TEST_LD_FLAGS)
	@echo "Build successful!"

$(TEST_OBJECT_FILES): $(TEST_OBJ)/%.o: %.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) -c $(CXX_FLAGS) -o $@ $<

env:
	@mkdir -p ./${ASSETS}
	@mkdir -p ./${OBJ}
	@mkdir -p ./${BIN}

test_env: env
	@mkdir -p ./${TEST_OBJ}

build: $(EXECUTABLE_FILES)

build_tests: $(TEST_EXECUTABLE_FILES)

clean:
	rm -rf ./$(BIN)/*
	rm -rf ./$(OBJ)/*

prepare:
	@echo Preparing assets
	rm -rf ./$(BIN)/$(ASSETS)
	cp -r ./$(LIB) ./$(BIN)/
	cp -r ./$(ASSETS) ./$(BIN)/

run: build prepare
	@echo Running $(EXECUTABLE_NAME)
	LD_LIBRARY_PATH=${LIB} ./$(BIN)/$(EXECUTABLE_NAME)

debug: build prepare
	@echo Running $(EXECUTABLE_NAME) with GDB server on port $(GDB_PORT)
	LD_LIBRARY_PATH=${LIB} gdbserver :$(GDB_PORT) $(BIN)/$(EXECUTABLE_NAME)

test: test_env build_tests
	@echo Running tests
	LD_LIBRARY_PATH=${LIB} ./$(BIN)/$(TEST_EXECUTABLE_NAME)

review:
	@echo
	@echo Running cppcheck
	@cppcheck . > /dev/null
	@echo Cppcheck complete
	@echo
	@echo Running doxygen
	@doxygen Doxyfile > /dev/null
	@echo Doxygen complete
	@echo
