#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "gauss.h"

// Функция для проверки решений
void test_gaussian_elimination() {
    // Пример из задания (а)
    std::vector<std::vector<double>> matrix_a = {
        {7, -2},
        {5, 3}
    };
    std::vector<double> rhs_a = {8, 19};
    std::vector<double> expected_a = {2, 3};

    gaussian_elimination(matrix_a, rhs_a, 1);
    std::vector<double> solution_a = back_substitution(matrix_a, rhs_a, 1);

    // Вывод решения для (a)
    std::cout << "Решение для системы (a): ";
    for (double x : solution_a) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Проверяем решение для (a)
    for (size_t i = 0; i < expected_a.size(); ++i) {
        assert(std::fabs(solution_a[i] - expected_a[i]) < 1e-6 && "Test case (a) failed!");
    }

    // Пример из задания (б)
    std::vector<std::vector<double>> matrix_b = {
        {3, -4},
        {2, 5}
    };
    std::vector<double> rhs_b = {-11, 8};
    std::vector<double> expected_b = {-1, 2};

    gaussian_elimination(matrix_b, rhs_b, 1);
    std::vector<double> solution_b = back_substitution(matrix_b, rhs_b, 1);

    // Вывод решения для (b)
    std::cout << "Решение для системы (b): ";
    for (double x : solution_b) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Проверяем решение для (b)
    for (size_t i = 0; i < expected_b.size(); ++i) {
        assert(std::fabs(solution_b[i] - expected_b[i]) < 1e-6 && "Test case (b) failed!");
    }

    // Пример из задания (в)
    std::vector<std::vector<double>> matrix_c = {
        {2, 3},
        {3, 4}
    };
    std::vector<double> rhs_c = {-1, -1};
    std::vector<double> expected_c = {1, -1};

    gaussian_elimination(matrix_c, rhs_c, 1);
    std::vector<double> solution_c = back_substitution(matrix_c, rhs_c, 1);

    // Вывод решения для (в)
    std::cout << "Решение для системы (c): ";
    for (double x : solution_c) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Проверяем решение для (в)
    for (size_t i = 0; i < expected_c.size(); ++i) {
        assert(std::fabs(solution_c[i] - expected_c[i]) < 1e-6 && "Test case (c) failed!");
    }

    std::cout << "Все тесты пройдены!" << std::endl;
}

int main() {
    test_gaussian_elimination();
    return 0;
}
