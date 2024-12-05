# # Variables
# CC = clang++
# CFLAGS = -std=c++11 -Xpreprocessor -fopenmp -I$(shell brew --prefix libomp)/include
# LDFLAGS = -L$(shell brew --prefix libomp)/lib -lomp
# SRC = $(wildcard *.cpp)
# BUILD_DIR = build

# # Default target program (если matrix_vector.cpp)
# DEFAULT_TARGET = matrix_vector

# # Default target
# all: $(BUILD_DIR) $(BUILD_DIR)/$(DEFAULT_TARGET)

# # Create build directory if it doesn't exist
# $(BUILD_DIR):
# 	mkdir -p $(BUILD_DIR)

# # Dynamic target for building any program
# $(BUILD_DIR)/%: %.cpp | $(BUILD_DIR)
# 	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# # Run the default target
# run: $(BUILD_DIR)/$(DEFAULT_TARGET)
# 	./$(BUILD_DIR)/$(DEFAULT_TARGET)

# # Run a specific program
# run-%: $(BUILD_DIR)/%
# 	./$(BUILD_DIR)/$*

# # Clean target
# clean:
# 	rm -rf $(BUILD_DIR)

build:
	c++ -std=c++11 -Xpreprocessor -fopenmp -I$(brew --prefix libomp)/include -L$(brew --prefix libomp)/lib -lomp matrix_vector.cpp -o build/matrix_vector
