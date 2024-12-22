# Компиляторы
CC = g++
MPI_CC = mpic++

# Общие флаги
CFLAGS = -std=c++17 -O2

# OpenMP флаги (для macOS)
OPENMP_FLAGS = -Xpreprocessor -fopenmp -I$(shell brew --prefix libomp)/include -L$(shell brew --prefix libomp)/lib -lomp

# Папка сборки
BUILD_DIR = build

# Названия целей
TARGETS = quicksort_sequential quicksort_omp quicksort_mpi

all: $(TARGETS)

# Последовательная версия
quicksort_sequential: task0/quicksort_sequential.cpp
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ task0/quicksort_sequential.cpp

# OpenMP версия
quicksort_omp: task1/quicksort_omp.cpp
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) -o $(BUILD_DIR)/$@ task1/quicksort_omp.cpp

# MPI версия
quicksort_mpi: task2/quicksort_mpi.cpp
	$(MPI_CC) $(CFLAGS) -o $(BUILD_DIR)/$@ task2/quicksort_mpi.cpp

# Очистка сборки
clean:
	rm -rf $(BUILD_DIR)/*
