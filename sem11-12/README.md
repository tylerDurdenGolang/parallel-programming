Лабораторная работа: Параллельная реализация алгоритмов сортировки

## Цель работы
Изучить эффективность параллельных алгоритмов сортировки с использованием технологий OpenMP и MPI на примере сортировки слиянием и быстрой сортировки. Исследовать время выполнения и ускорение параллельных алгоритмов в сравнении с последовательным методом.

## Описание экспериментов

### Алгоритмы:
- Последовательная реализация сортировки.
- Параллельная реализация с использованием OpenMP.
- Параллельная реализация с использованием MPI.

### Параметры:
- Размеры массивов: 10,000, 50,000, 100,000, 500,000, 1,000,000, 5,000,000, 10,000,000 элементов.
- Количество потоков (OpenMP): 2, 4, 8.
- Количество процессов (MPI): 2, 4, 8.

### Метрики:
- Время выполнения.
- Ускорение параллельных алгоритмов относительно последовательного.

## Результаты экспериментов
Результаты экспериментов сохранены в виде таблиц и графиков в следующих файлах:

### Merge Sort
**Таблицы:**
- `merge_sort/mpi_results/final_results_mpi_table.xlsx` — результаты MPI.
- `merge_sort/openmp_results/final_results_openmp_table.xlsx` — результаты OpenMP.

**Графики:**
- `merge_sort/mpi_results/mpi_execution_time.png` — время выполнения MPI.
- `merge_sort/mpi_results/mpi_speedup.png` — ускорение MPI.
- `merge_sort/openmp_results/openmp_execution_time.png` — время выполнения OpenMP.
- `merge_sort/openmp_results/openmp_speedup.png` — ускорение OpenMP.

### Quick Sort
**Таблицы:**
- `quick_sort/mpi_results/final_results_mpi_table.xlsx` — результаты MPI.
- `quick_sort/openmp_results/final_results_openmp_table.xlsx` — результаты OpenMP.

**Графики:**
- `quick_sort/mpi_results/mpi_execution_time.png` — время выполнения MPI.
- `quick_sort/mpi_results/mpi_speedup.png` — ускорение MPI.
- `quick_sort/openmp_results/openmp_execution_time.png` — время выполнения OpenMP.
- `quick_sort/openmp_results/openmp_speedup.png` — ускорение OpenMP.

## Выводы
- MPI показал лучшее ускорение для больших массивов благодаря более равномерному распределению нагрузки между процессами.
- OpenMP также продемонстрировал высокую производительность, но ограничен количеством потоков на одном узле.
- Для малых массивов накладные расходы на создание потоков и процессов снижают эффективность параллельных реализаций.

## Рекомендации
- Использовать MPI для распределённых систем и больших объёмов данных.
- Использовать OpenMP для оптимизации на локальных многопроцессорных системах.