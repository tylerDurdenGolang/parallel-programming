#include <vector>
#include <omp.h>

// Функция для LU-разложения (распараллелена)
void lu_decomposition(const std::vector<std::vector<double>> &matrix,
                      std::vector<std::vector<double>> &L,
                      std::vector<std::vector<double>> &U,
                      int threads) {
    int n = matrix.size();
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    #pragma omp parallel num_threads(threads)
    {
        for (int i = 0; i < n; ++i) {
            // Вычисление U
            #pragma omp for
            for (int j = i; j < n; ++j) {
                U[i][j] = matrix[i][j];
                for (int k = 0; k < i; ++k) {
                    U[i][j] -= L[i][k] * U[k][j];
                }
            }

            // Вычисление L
            #pragma omp for
            for (int j = i; j < n; ++j) {
                if (i == j) {
                    L[i][i] = 1.0;
                } else {
                    L[j][i] = matrix[j][i];
                    for (int k = 0; k < i; ++k) {
                        L[j][i] -= L[j][k] * U[k][i];
                    }
                    L[j][i] /= U[i][i];
                }
            }
        }
    }
}

// Решение системы методом LU-разложения
std::vector<double> solve_lu(const std::vector<std::vector<double>> &L,
                             const std::vector<std::vector<double>> &U,
                             const std::vector<double> &b) {
    int n = L.size();
    std::vector<double> y(n, 0.0);
    std::vector<double> x(n, 0.0);

    // Прямой ход для нахождения y
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Обратный ход для нахождения x
    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }

    return x;
}