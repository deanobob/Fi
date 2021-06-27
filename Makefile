# Makefile

# Returns 1 if Linux, else 0
IS_LINUX := $(shell uname -a | grep -c Linux)

# Define paths and library files
INC_PATH := -Isource/ \
            -Isource/messaging/ \
		    -Isource/messaging/messages/ \
			-Isource/core/ \
			-Isource/services/ \
			-Isource/services/console/ \
			-Isource/services/console/commands/ \
            -Isource/input/ \
            -Isource/framework/ \
            -Isource/utilities/ \
			-Ithird_party/
LIB_PATH := -L lib/ \
            -L/usr/local/lib
LIBS     := -lpthread -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf

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
TEST_EXECUTABLE_NAME := Malon_test

# GDB configuration
GDB_PORT := 6000

# Important folders
BIN      := bin
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
	@$(CXX) -o $@ $^ $(LD_FLAGS)
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) -c $(CXX_FLAGS) -o $@ $<

$(TEST_EXECUTABLE_FILES): $(TEST_OBJECT_FILES)
	@$(CXX) -o $@ $^ $(LD_FLAGS)
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
	cp -r ./$(ASSETS) ./$(BIN)/

run: build prepare
	@echo Running $(EXECUTABLE_NAME)
	./$(BIN)/$(EXECUTABLE_NAME)

debug: build prepare
	@echo Running $(EXECUTABLE_NAME) with GDB server on port $(GDB_PORT)
	gdbserver :$(GDB_PORT) $(BIN)/$(EXECUTABLE_NAME)

test: test_env build_tests
	@echo Running tests
	./$(BIN)/$(TEST_EXECUTABLE_NAME)

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
