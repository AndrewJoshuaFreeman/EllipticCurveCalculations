# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -O2

# Target executable
TARGET = exe

# Source and header files (now in src/ and include/)
SRCS = src/main.cpp
HEADERS = include/headers.h

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -Iinclude $(SRCS) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

.PHONY: all run clean
