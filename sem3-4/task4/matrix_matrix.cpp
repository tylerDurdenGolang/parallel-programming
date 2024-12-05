#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>
#include <fstream>
#include <algorithm> // Для std::min

// Функция блочного умножения матриц
void block_matrix_multiplication(const std::vector<std::vector<double>> &matrixA,
                                  const std::vector<std::vector<double>> &matrixB,
                                  std::vector<std::vector<double>> &result,
                                  int block_size, int threads) {
    int rows = matrixA.size();
    int cols = matrixB[0].size();
    int inner_dim = matrixB.size();

    #pragma omp parallel for collapse(2) num_threads(threads)
    for (int bi = 0; bi < rows; bi += block_size) {
        for (int bj = 0; bj < cols; bj += block_size) {
            for (int bk = 0; bk < inner_dim; bk += block_size) {
                // Предварительное вычисление границ блоков
                int i_max = std::min(bi + block_size, rows);
                int j_max = std::min(bj + block_size, cols);
                int k_max = std::min(bk + block_size, inner_dim);

                // Умножение блоков
                for (int i = bi; i < i_max; ++i) {
                    for (int j = bj; j < j_max; ++j) {
                        double temp = 0.0;
                        #pragma omp simd reduction(+:temp)
                        for (int k = bk; k < k_max; ++k) {
                            temp += matrixA[i][k] * matrixB[k][j];
                        }
                        result[i][j] += temp;
                    }
                }
            }
        }
    }
}

int main() {
    std::vector<int> matrix_sizes = {1000, 2000, 4000, 8000};
    std::vector<int> threads_count = {2, 4, 8, 16};
    std::vector<int> block_sizes = {128, 256, 512}; // Размеры блоков

    // Открытие файла с буферизацией
    std::ofstream csv_file("block_matrix_results_optimized.csv", std::ios::out | std::ios::trunc);
    csv_file << "MatrixSize,Threads,BlockSize,ExecutionTime\n";

    std::cout << std::setw(15) << "Размер матрицы"
              << std::setw(15) << "Потоки"
              << std::setw(15) << "Размер блока"
              << std::setw(20) << "Время вычисления (сек)"
              << std::endl;

    for (int size : matrix_sizes) {
        for (int threads : threads_count) {
            for (int block_size : block_sizes) {
                // Инициализация матриц
                std::vector<std::vector<double>> matrixA(size, std::vector<double>(size));
                std::vector<std::vector<double>> matrixB(size, std::vector<double>(size));
                std::vector<std::vector<double>> result(size, std::vector<double>(size, 0.0));

                // Заполнение матриц случайными значениями (векторизация недоступна, но ускорение достигается)
                #pragma omp parallel for collapse(2) num_threads(threads)
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        matrixA[i][j] = static_cast<double>(rand()) / RAND_MAX;
                        matrixB[i][j] = static_cast<double>(rand()) / RAND_MAX;
                    }
                }

                // Измерение времени выполнения
                double start_time = omp_get_wtime();
                block_matrix_multiplication(matrixA, matrixB, result, block_size, threads);
                double end_time = omp_get_wtime();

                double execution_time = end_time - start_time;

                // Вывод в консоль
                std::cout << std::setw(15) << size
                          << std::setw(15) << threads
                          << std::setw(15) << block_size
                          << std::setw(20) << execution_time
                          << std::endl;

                // Запись в файл
                csv_file << size << "," << threads << "," << block_size << "," << execution_time << "\n";
            }
        }
    }

    csv_file.close();
    return 0;
}
