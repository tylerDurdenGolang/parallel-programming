#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>
#include <string>
#include "gauss.h"

// Функция для решения и вывода системы
void solve_system(const std::vector<std::vector<double>> &matrix, const std::vector<double> &rhs, const std::string &label, int threads) {
    auto m = matrix; // Копируем матрицу для модификации
    auto b = rhs;    // Копируем столбец свободных членов
    gaussian_elimination(m, b, threads);
    std::vector<double> solution = back_substitution(m, b, threads);

    std::cout << "Решение системы " << label << ": ";
    for (double x : solution) {
        std::cout << std::fixed << std::setprecision(6) << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    int threads = 4; // Количество потоков

    // Система (г)
    std::vector<std::vector<double>> matrix_g = {
        {1, 3, -1},
        {2, 4, 3},
        {3, -2, 5}
    };
    std::vector<double> rhs_g = {-2, 3, 13};

    // Система (ж)
    std::vector<std::vector<double>> matrix_h = {
        {4, -2, 1},
        {1, 3, -2},
        {3, -1, 4}
    };
    std::vector<double> rhs_h = {6, 5, 5};

    // Система (д)
    std::vector<std::vector<double>> matrix_d = {
        {2, -1, 1},
        {3, -2, -3},
        {1, 1, 1}
    };
    std::vector<double> rhs_d = {0, 11, 6};

    // Система (е)
    std::vector<std::vector<double>> matrix_e = {
        {1, 1, -1},
        {2, 3, -4},
        {7, -1, -3}
    };
    std::vector<double> rhs_e = {6, 21, 6};

    // Система (и)
    std::vector<std::vector<double>> matrix_i = {
        {3, -1, 2},
        {1, 3, 0},
        {-1, 2, 3}
    };
    std::vector<double> rhs_i = {1, -1, 7};

    // Система (к)
    std::vector<std::vector<double>> matrix_k = {
        {5732, 2134, 2134},
        {2134, 5732, 2134},
        {2134, 2134, 5732}
    };
    std::vector<double> rhs_k = {7866, 670, 11464};

    // Решение систем
    solve_system(matrix_g, rhs_g, "(г)", threads);
    solve_system(matrix_h, rhs_h, "(ж)", threads);
    solve_system(matrix_d, rhs_d, "(д)", threads);
    solve_system(matrix_e, rhs_e, "(е)", threads);
    solve_system(matrix_i, rhs_i, "(и)", threads);
    solve_system(matrix_k, rhs_k, "(к)", threads);

    return 0;
}
