#include <iostream>
#include <omp.h>
#include <cmath>

int main() {
    // const double tolerance = 1e-10;  // Заданная точность
    const double tolerance = 0.001;  // Заданная точность
    const long long max_iterations = 1000000000; // Максимальное количество итераций
    int num_threads[] = {1, 2, 4, 8, 16}; // Число потоков для тестирования

    printf("Число потоков\tВремя выполнения (секунды)\n");

    for (int threads = 0; threads < 5; ++threads) {
        double pi = 0.0;
        double start_time = omp_get_wtime();

        omp_set_num_threads(num_threads[threads]);
        
        #pragma omp parallel
        {
            double local_sum = 0.0;
            #pragma omp for
            for (long long n = 0; n < max_iterations; ++n) {
                double term = (n % 2 == 0 ? 1.0 : -1.0) / (2.0 * n + 1.0);
                local_sum += term;
            }

            #pragma omp atomic
            pi += local_sum;
        }
        pi *= 4.0;

        double end_time = omp_get_wtime();
        printf("%d\t\t%f секунд\n", num_threads[threads], end_time - start_time);

        // Проверка достижения точности
        if (fabs(pi - M_PI) < tolerance) {
            printf("Точность достигнута для %d потоков\n", num_threads[threads]);
        } else {
            printf("Точность не достигнута для %d потоков, результат: %f\n", num_threads[threads], pi);
        }
    }

    return 0;
}
