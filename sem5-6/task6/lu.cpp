#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <omp.h>
#include "lu.h"

// Умножение матриц L и U для проверки A = L * U
std::vector<std::vector<double>> multiply_matrices(const std::vector<std::vector<double>> &L,
                                                   const std::vector<std::vector<double>> &U) {
    int n = L.size();
    std::vector<std::vector<double>> result(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += L[i][k] * U[k][j];
            }
        }
    }
    return result;
}

// Обработка одной системы уравнений
void process_system(const std::vector<std::vector<double>> &matrix,
                    const std::vector<double> &rhs,
                    const std::string &label,
                    int threads,
                    std::ofstream &output) {
    output << "Система " << label << ":\n";

    // Выполнение LU-разложения
    std::vector<std::vector<double>> L, U;
    lu_decomposition(matrix, L, U, threads);

    // Проверка разложения: перемножение L и U
    std::vector<std::vector<double>> A_reconstructed = multiply_matrices(L, U);

    // Вывод матриц L, U
    output << "Матрица L:\n";
    for (const auto &row : L) {
        for (double val : row) {
            output << std::setw(10) << val << " ";
        }
        output << std::endl;
    }
    output << "Матрица U:\n";
    for (const auto &row : U) {
        for (double val : row) {
            output << std::setw(10) << val << " ";
        }
        output << std::endl;
    }

    // Решение системы
    std::vector<double> solution = solve_lu(L, U, rhs);
    output << "Решение системы:\n";
    for (double x : solution) {
        output << std::fixed << std::setprecision(6) << x << " ";
    }
    output << std::endl;

    // Проверка A = L * U
    output << "Восстановленная матрица A (для проверки):\n";
    for (const auto &row : A_reconstructed) {
        for (double val : row) {
            output << std::setw(10) << val << " ";
        }
        output << std::endl;
    }
    output << "------------------------\n";
}

int main() {
    int threads = 4; // Количество потоков

    // Матрицы систем (а) - (к)
    std::vector<std::vector<std::vector<double>>> matrices = {
        {{7, -2}, {5, 3}},                          // (а)
        {{3, -4}, {2, 5}},                          // (б)
        {{2, 3}, {3, 4}},                           // (в)
        {{1, 3, -1}, {2, 4, 3}, {3, -2, 5}},        // (г)
        {{4, -2, 1}, {1, 3, -2}, {3, -1, 4}},       // (ж)
        {{2, -1, 1}, {3, -2, -3}, {1, 1, 1}},       // (д)
        {{1, 1, -1}, {2, 3, -4}, {7, -1, -3}},      // (е)
        {{3, -1, 2}, {1, 3, 0}, {-1, 2, 3}},        // (и)
        {{5732, 2134, 2134}, {2134, 5732, 2134}, {2134, 2134, 5732}} // (к)
    };

    // Свободные члены систем (а) - (к)
    std::vector<std::vector<double>> rhs = {
        {8, 19},                  // (а)
        {-11, 8},                 // (б)
        {-1, -1},                 // (в)
        {-2, 3, 13},              // (г)
        {6, 5, 5},                // (ж)
        {0, 11, 6},               // (д)
        {6, 21, 6},               // (е)
        {1, -1, 7},               // (и)
        {7866, 670, 11464}        // (к)
    };

    // Метки систем (а) - (к)
    std::vector<std::string> labels = {"(а)", "(б)", "(в)", "(г)", "(ж)", "(д)", "(е)", "(и)", "(к)"};

    // Открываем файл для записи
    std::ofstream output("lu_results.txt");

    for (size_t i = 0; i < matrices.size(); ++i) {
        process_system(matrices[i], rhs[i], labels[i], threads, output);
    }

    output.close();
    std::cout << "Результаты сохранены в файл lu_results.txt" << std::endl;

    return 0;
}
