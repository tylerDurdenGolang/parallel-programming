#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip> // Для форматированного вывода
#include <fstream> // Для вывода в файл

// Функция умножения матрицы на вектор
void matrix_vector_multiplication(const std::vector<std::vector<double>> &matrix, 
                                  const std::vector<double> &vector, 
                                  std::vector<double> &result, 
                                  int threads) {
    int rows = matrix.size();
    int cols = vector.size();

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < rows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    std::vector<int> matrix_sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    std::vector<int> threads_count = {2, 4, 8, 16};

    // Открытие файла для записи
    std::ofstream csv_file("matrix_vector_results.csv");
    csv_file << "MatrixSize,Threads,RandomValuesTime,LinearValuesTime\n";

    // Вывод шапки таблицы в консоль
    std::cout << std::setw(15) << "Строк в матрице" 
              << std::setw(15) << "\tПотоки"
              << std::setw(25) << "\tСлучайные значения (сек)"
              << std::setw(25) << "\tЛинейные значения (сек)" 
              << std::endl;

    for (int size : matrix_sizes) {
        // Инициализация матрицы и вектора
        std::vector<std::vector<double>> matrix(size, std::vector<double>(size));
        std::vector<double> vector(size), result(size, 0.0);

        for (int threads : threads_count) {
            // Заполнение случайными значениями
            for (int i = 0; i < size; i++) {
                vector[i] = static_cast<double>(rand()) / RAND_MAX;
                for (int j = 0; j < size; j++) {
                    matrix[i][j] = static_cast<double>(rand()) / RAND_MAX;
                }
            }
            double start_random = omp_get_wtime();
            matrix_vector_multiplication(matrix, vector, result, threads);
            double end_random = omp_get_wtime();
            double random_time = end_random - start_random;

            // Заполнение линейными значениями
            for (int i = 0; i < size; i++) {
                vector[i] = i + 1;
                for (int j = 0; j < size; j++) {
                    matrix[i][j] = j + 1;
                }
            }
            double start_linear = omp_get_wtime();
            matrix_vector_multiplication(matrix, vector, result, threads);
            double end_linear = omp_get_wtime();
            double linear_time = end_linear - start_linear;

            // Вывод в консоль
            std::cout << std::setw(15) << size 
                      << std::setw(15) << threads 
                      << std::setw(25) << random_time 
                      << std::setw(25) << linear_time 
                      << std::endl;

            // Запись в файл
            csv_file << size << "," << threads << "," 
                     << random_time << "," << linear_time << "\n";
        }
    }

    csv_file.close();
    return 0;
}
