#!/bin/bash

# Очистка старых файлов результатов
rm -f results_mpi.csv

# Размеры массивов
ARRAY_SIZES=(10000 50000 100000 500000 1000000 5000000 10000000)
PROCESSES=(2 4 8) # Количество процессов

# Проверка существования программы
check_program() {
    if ! command -v mpirun &> /dev/null; then
        echo "Error: 'mpirun' not found. Make sure MPI is installed and available in PATH."
        exit 1
    fi

    if [ ! -f "$1" ]; then
        echo "Error: Program $1 not found. Ensure it is compiled."
        exit 1
    fi
}

PROGRAM="build/mergesort_mpi"
OUTPUT_FILE="results_mpi.csv"

check_program $PROGRAM
echo "ArraySize,Processes,ExecutionTime" > $OUTPUT_FILE

for SIZE in "${ARRAY_SIZES[@]}"; do
    for PROC in "${PROCESSES[@]}"; do
        echo "Running MPI mergesort for array size $SIZE with $PROC processes..."
        
        # Выполнение программы
        OUTPUT=$(mpirun --oversubscribe -np $PROC $PROGRAM $SIZE)

        # Извлечение времени выполнения
        TIME=$(echo "$OUTPUT" | grep -i "execution time:" | awk '{print $4}')

        # Проверка, удалось ли извлечь время
        if [[ -z "$TIME" ]]; then
            echo "Error: Unable to extract execution time for array size $SIZE and $PROC processes."
            continue
        fi

        # Запись результатов
        echo "$SIZE,$PROC,$TIME" >> $OUTPUT_FILE
    done
done

echo "MPI results saved to $OUTPUT_FILE"
