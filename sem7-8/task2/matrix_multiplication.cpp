#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Генерация случайного вектора
std::vector<int> generate_vector(int size) {
    std::vector<int> vec(size);
    for (int &val : vec) {
        val = rand() % 100;
    }
    return vec;
}

// Генерация случайной матрицы (в виде одномерного массива)
std::vector<int> generate_matrix(int rows, int cols) {
    std::vector<int> matrix(rows * cols);
    for (int &val : matrix) {
        val = rand() % 100;
    }
    return matrix;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int ProcRank, ProcNum;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    srand(time(nullptr) + ProcRank);

    const int rows = 1000, cols = 1000;
    const int rows_per_proc = rows / ProcNum;

    std::vector<int> matrix;
    std::vector<int> vec;
    std::vector<int> result(rows, 0);

    if (ProcRank == 0) {
        matrix = generate_matrix(rows, cols);
        vec = generate_vector(cols);
    } else {
        vec.resize(cols);
    }

    MPI_Bcast(vec.data(), cols, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<int> local_matrix(rows_per_proc * cols);

    MPI_Scatter(matrix.data(), rows_per_proc * cols, MPI_INT, 
                local_matrix.data(), rows_per_proc * cols, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    std::vector<int> local_result(rows_per_proc, 0);
    for (int i = 0; i < rows_per_proc; ++i) {
        for (int j = 0; j < cols; ++j) {
            local_result[i] += local_matrix[i * cols + j] * vec[j];
        }
    }

    MPI_Gather(local_result.data(), rows_per_proc, MPI_INT, 
               result.data(), rows_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (ProcRank == 0) {
        double execution_time = end_time - start_time;
        std::cout << execution_time << std::endl;
    }

    MPI_Finalize();
    return 0;
}
