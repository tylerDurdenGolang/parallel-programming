#!/bin/bash

# Очистка старых файлов результатов
rm -f results_openmp.csv

# Размеры массивов
ARRAY_SIZES=(10000 50000 100000 500000 1000000 5000000 10000000)
THREADS=(2 4 6 8) # Количество потоков

# Проверка существования программы
check_program() {
    if [ ! -f "$1" ]; then
        echo "Error: Program $1 not found. Ensure it is compiled."
        exit 1
    fi
}

PROGRAM="build/quicksort_omp"
OUTPUT_FILE="results_openmp.csv"

check_program $PROGRAM
echo "ArraySize,Threads,ExecutionTime" > $OUTPUT_FILE

for SIZE in "${ARRAY_SIZES[@]}"; do
    for THREAD in "${THREADS[@]}"; do
        echo "Running OpenMP quicksort for array size $SIZE with $THREAD threads..."
        export OMP_NUM_THREADS=$THREAD
        OUTPUT=$($PROGRAM $SIZE $THREAD)

        # Извлечение времени выполнения
        TIME=$(echo "$OUTPUT" | grep "Execution time:" | awk '{print $3}')

        # Запись результатов
        echo "$SIZE,$THREAD,$TIME" >> $OUTPUT_FILE
    done
done

echo "OpenMP results saved to $OUTPUT_FILE"
