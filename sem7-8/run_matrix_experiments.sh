#!/bin/bash

# Очистка файла результатов
echo "Processes,ExecutionTime" > matrix_results.csv

# Компиляция программы
make

# Количество процессов
PROCESSES=(2 5 10)

# Запуск экспериментов
for PROC in "${PROCESSES[@]}"; do
    echo "Запуск с $PROC процессами..."
    TIME=$(mpirun -np $PROC ./build/matrix_multiplication | tail -n 1)
    echo "$PROC,$TIME" >> matrix_results.csv
done

echo "Результаты сохранены в matrix_results.csv"
