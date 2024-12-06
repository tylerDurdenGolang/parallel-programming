#!/bin/bash

# Очистка файла результатов
echo "Processes,ExecutionTime" > vector_results.csv

# Название программы
PROGRAM="vector_sum"
# Количество процессов для тестирования
PROCESSES=(2 4 6 12)
# Размер вектора
VECTOR_SIZE=120000

# Компиляция программы
make

# Запуск экспериментов
for PROC in "${PROCESSES[@]}"; do
    echo "Запуск с $PROC процессами..."
    TIME=$(mpirun --oversubscribe -np $PROC ./build/$PROGRAM $VECTOR_SIZE | tail -n 1)
    echo "$PROC,$TIME" >> vector_results.csv
done

echo "Тестирование завершено. Результаты сохранены в vector_results.csv"
