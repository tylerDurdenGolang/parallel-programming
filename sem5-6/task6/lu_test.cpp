#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "lu.h" // Подключение заголовочного файла с функцией lu_decomposition

// Функция для проверки точности решений
void test_lu_decomposition() {
    // Система (а)
    std::vector<std::vector<double>> matrix_a = {
        {7, -2},
        {5, 3}
    };
    std::vector<double> rhs_a = {8, 19};
    std::vector<double> expected_a = {2, 3};

    // Система (б)
    std::vector<std::vector<double>> matrix_b = {
        {3, -4},
        {2, 5}
    };
    std::vector<double> rhs_b = {-11, 8};
    std::vector<double> expected_b = {-1, 2};

    // Система (в)
    std::vector<std::vector<double>> matrix_c = {
        {2, 3},
        {3, 4}
    };
    std::vector<double> rhs_c = {-1, -1};
    std::vector<double> expected_c = {1, -1};

    // Тестируем систему (а)
    std::vector<std::vector<double>> L_a, U_a;
    lu_decomposition(matrix_a, L_a, U_a, 1);
    std::vector<double> solution_a = solve_lu(L_a, U_a, rhs_a);

    std::cout << "Решение для системы (а): ";
    for (double x : solution_a) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < expected_a.size(); ++i) {
        assert(std::fabs(solution_a[i] - expected_a[i]) < 1e-6 && "Test case (a) failed!");
    }

    // Тестируем систему (б)
    std::vector<std::vector<double>> L_b, U_b;
    lu_decomposition(matrix_b, L_b, U_b, 1);
    std::vector<double> solution_b = solve_lu(L_b, U_b, rhs_b);

    std::cout << "Решение для системы (б): ";
    for (double x : solution_b) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < expected_b.size(); ++i) {
        assert(std::fabs(solution_b[i] - expected_b[i]) < 1e-6 && "Test case (b) failed!");
    }

    // Тестируем систему (в)
    std::vector<std::vector<double>> L_c, U_c;
    lu_decomposition(matrix_c, L_c, U_c, 1);
    std::vector<double> solution_c = solve_lu(L_c, U_c, rhs_c);

    std::cout << "Решение для системы (в): ";
    for (double x : solution_c) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < expected_c.size(); ++i) {
        assert(std::fabs(solution_c[i] - expected_c[i]) < 1e-6 && "Test case (c) failed!");
    }

    std::cout << "Все тесты успешно пройдены!" << std::endl;
}

int main() {
    test_lu_decomposition();
    return 0;
}
