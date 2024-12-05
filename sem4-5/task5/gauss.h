#include <vector>
#include <omp.h>
#include <fstream>

// Параллельный метод Гаусса
void gaussian_elimination(std::vector<std::vector<double>> &matrix, std::vector<double> &rhs, int threads) {
    int n = matrix.size();

    #pragma omp parallel num_threads(threads)
    {
        for (int k = 0; k < n; ++k) {
            // Нормализация главной строки
            #pragma omp single
            {
                double pivot = matrix[k][k];
                for (int j = k; j < n; ++j) {
                    matrix[k][j] /= pivot;
                }
                rhs[k] /= pivot;
            }

            // Барьер для синхронизации
            #pragma omp barrier

            // Вычитание из последующих строк
            #pragma omp for schedule(dynamic, 10)
            for (int i = k + 1; i < n; ++i) {
                double factor = matrix[i][k];
                for (int j = k; j < n; ++j) {
                    matrix[i][j] -= factor * matrix[k][j];
                }
                rhs[i] -= factor * rhs[k];
            }
        }
    }
}

// Обратный ход
std::vector<double> back_substitution(const std::vector<std::vector<double>> &matrix, const std::vector<double> &rhs, int threads) {
    int n = matrix.size();
    std::vector<double> solution(n);

    #pragma omp parallel num_threads(threads)
    {
        for (int i = n - 1; i >= 0; --i) {
            #pragma omp single
            {
                solution[i] = rhs[i];
                for (int j = i + 1; j < n; ++j) {
                    solution[i] -= matrix[i][j] * solution[j];
                }
                solution[i] /= matrix[i][i];
            }

            // Барьер для синхронизации
            #pragma omp barrier
        }
    }
    return solution;
}
