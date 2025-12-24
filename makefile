CXX := g++
CXXFLAGS := -std=c++17 -O3 -ffast-math -Wall -Wextra -pedantic
INCLUDES := -Iinclude

SRC_DIR := src
OBJ_DIR := obj

TARGET := eccalc

SRCS := $(SRC_DIR)/main.cpp \
        $(SRC_DIR)/math_utils.cpp \
        $(SRC_DIR)/ellipticCurveCalculations.cpp

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ_DIR)

