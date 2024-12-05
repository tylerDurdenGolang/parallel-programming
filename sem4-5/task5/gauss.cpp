#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include "gauss.h"

int main() {
    std::vector<int> matrix_sizes = {500, 1000, 3000}; // Размеры матриц
    std::vector<int> threads_count = {3, 4};  // Количество потоков
    std::ofstream csv_file("gauss_results.csv");
    csv_file << "MatrixSize,Threads,ExecutionTime\n";

    for (int size : matrix_sizes) {
        for (int threads : threads_count) {
            // Генерация случайной матрицы
            std::vector<std::vector<double>> matrix(size, std::vector<double>(size));
            std::vector<double> rhs(size);

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    matrix[i][j] = rand() % 100 + 1;
                }
                rhs[i] = rand() % 100 + 1;
            }

            double start_time = omp_get_wtime();
            gaussian_elimination(matrix, rhs, threads);
            std::vector<double> solution = back_substitution(matrix, rhs, threads);
            double end_time = omp_get_wtime();

            double elapsed_time = end_time - start_time;
            csv_file << size << "," << threads << "," << elapsed_time << "\n";

            std::cout << "Matrix Size: " << size << ", Threads: " << threads
                      << ", Time: " << elapsed_time << " seconds" << std::endl;
        }
    }

    csv_file.close();
    return 0;
}
