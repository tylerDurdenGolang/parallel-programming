#include <stdio.h>
#include <omp.h>
#include <math.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {

#ifdef _OPENMP 
    printf("Поддержка OpenMP включена\n");
#else
    printf("OpenMP не поддерживается\n");
#endif

    int num_threads = 1;  // количество потоков
    int sum = 0;
    double wtime;

    // Задание 1: Установка количества потоков
    omp_set_num_threads(num_threads);
    printf("Количество потоков: %d\n", omp_get_max_threads());

    // Задание 3: Засекаем время начала
    wtime = omp_get_wtime();

    // Задание 2: Подсчёт суммы простых чисел в диапазоне
    #pragma omp parallel for reduction(+:sum)
    for (int i = 2; i <= 100000; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }

    // Засекаем время окончания
    wtime = omp_get_wtime() - wtime;

    printf("Сумма простых чисел: %d\n", sum);
    printf("Время выполнения: %f секунд\n", wtime);

    return 0;
}
