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
TARGETS = mergesort_sequential mergesort_omp mergesort_mpi

all: $(TARGETS)

# Последовательная версия
mergesort_sequential: task0/mergesort_sequential.cpp
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ task0/mergesort_sequential.cpp

# OpenMP версия
mergesort_omp: task1/mergesort_omp.cpp
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) -o $(BUILD_DIR)/$@ task1/mergesort_omp.cpp

# MPI версия
mergesort_mpi: task2/mergesort_mpi.cpp
	$(MPI_CC) $(CFLAGS) -o $(BUILD_DIR)/$@ task2/mergesort_mpi.cpp

# Очистка сборки
clean:
	rm -rf $(BUILD_DIR)/*
