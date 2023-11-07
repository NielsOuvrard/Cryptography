##
## Makefile for cpp
##

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = test

# Source files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# Output executable name
NAME = mypgp

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -I./$(INCLUDE_DIR)
CXXFLAGS_WARNINGS = -Wall -Wextra -Werror
CXXFLAGS_DEBUG = -g -O0 -g3

all: $(NAME)

$(NAME): $(OBJ)
	@ $(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@ $(CXX) $(CXXFLAGS) -c $< -o $@

# Debug target (with additional flags)
debug: CXXFLAGS += $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARNINGS)
debug: re

$(BUILD_DIR):
	@ mkdir -p $(BUILD_DIR)

test: $(NAME)
	@ ./$(TEST_DIR)/test.sh

clean:
	@ rm -rf $(BUILD_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug test