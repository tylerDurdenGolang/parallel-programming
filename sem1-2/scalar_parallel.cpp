#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 110000000

double a[N + 1], b[N + 1];
double gDotProduct;

int main() {
    // Инициализация векторов
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        a[i] = 1.034;
        b[i] = 1.057;
    }

    // Засекаем время начала
    auto start = omp_get_wtime();

    // Распараллеливание скалярного произведения
    #pragma omp parallel for reduction(+:gDotProduct)
    for (int i = 0; i < N; i++) {
        gDotProduct += a[i] * b[i];
    }

    // Засекаем время окончания
    auto stop = omp_get_wtime();

    printf("Computed value of vector sum: ");
    // Выводим скалярное произведение
    printf("sum = %f\n", gDotProduct);
    // Выводим время выполнения
    printf("time = %f seconds\n", stop - start);

    return 0;
}
