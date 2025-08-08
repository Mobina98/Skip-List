# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -Isubmodules/googletest/googletest/include

# Sources
SRC = src/main.cpp
TEST_SRC = tests/test_skip_list.cpp

# GoogleTest Build
GTEST_DIR = submodules/googletest
GTEST_BUILD = $(GTEST_DIR)/build
GTEST_LIB = $(GTEST_BUILD)/lib/libgtest.a $(GTEST_BUILD)/lib/libgtest_main.a

# Targets
all: skiplist_demo

# Build demo executable
skiplist_demo: $(SRC) include/skip_list.hpp
	$(CXX) $(CXXFLAGS) $(SRC) -o skiplist_demo

# Build GoogleTest libraries if not present
$(GTEST_LIB):
	cmake -S $(GTEST_DIR) -B $(GTEST_BUILD)
	cmake --build $(GTEST_BUILD)

# Build test binary
test: $(GTEST_LIB) $(TEST_SRC) include/skip_list.hpp
	$(CXX) $(CXXFLAGS) -pthread $(TEST_SRC) $(GTEST_LIB) -o tests/test_skip_list

# Run tests
run_tests: test
	./tests/test_skip_list

# Clean build artifacts
clean:
	rm -f skiplist_demo tests/test_skip_list
