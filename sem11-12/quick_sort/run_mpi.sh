#!/bin/bash

# Очистка старых файлов результатов
rm -f results_mpi.csv

# Размеры массивов
ARRAY_SIZES=(10000 50000 100000 500000 1000000 5000000 10000000)
PROCESSES=(2 4 8) # Количество процессов

# Проверка существования программы
check_program() {
    if [ ! -f "$1" ]; then
        echo "Error: Program $1 not found. Ensure it is compiled."
        exit 1
    fi
}

PROGRAM="build/quicksort_mpi"
OUTPUT_FILE="results_mpi.csv"

check_program $PROGRAM
echo "ArraySize,Processes,ExecutionTime" > $OUTPUT_FILE

for SIZE in "${ARRAY_SIZES[@]}"; do
    for PROC in "${PROCESSES[@]}"; do
        echo "Running MPI quicksort for array size $SIZE with $PROC processes..."
        OUTPUT=$(mpirun --oversubscribe -np $PROC $PROGRAM $SIZE)

        # Извлечение времени выполнения
        TIME=$(echo "$OUTPUT" | grep "Execution time:" | awk '{print $3}')

        # Запись результатов
        echo "$SIZE,$PROC,$TIME" >> $OUTPUT_FILE
    done
done

echo "MPI results saved to $OUTPUT_FILE"
