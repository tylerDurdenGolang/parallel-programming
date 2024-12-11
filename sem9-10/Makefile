# Компиляторы
CC = g++
MPI_CC = mpic++

# Общие флаги
CFLAGS = -std=c++11 -O2

# OpenMP флаги (для macOS)
OPENMP_FLAGS = -Xpreprocessor -fopenmp -I$(shell brew --prefix libomp)/include -L$(shell brew --prefix libomp)/lib -lomp

# Папка сборки
BUILD_DIR = build

# Названия целей
TARGETS = solve_system solve_system_omp solve_system_mpi

all: $(TARGETS)

# Последовательная версия
solve_system: $(BUILD_DIR) task1/main.cpp
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ task1/main.cpp

# OpenMP версия
solve_system_omp: $(BUILD_DIR) task2/main.cpp
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) -o $(BUILD_DIR)/$@ task2/main.cpp

# MPI версия
solve_system_mpi: $(BUILD_DIR) task3/main.cpp
	$(MPI_CC) $(CFLAGS) -o $(BUILD_DIR)/$@ task3/main.cpp

# Очистка сборки
clean:
	rm -rf $(BUILD_DIR)/*
