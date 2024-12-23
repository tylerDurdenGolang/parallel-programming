#!/bin/bash

# Очистка старых файлов результатов
rm -f results_sequential.csv

# Размеры массивов
ARRAY_SIZES=(10000 50000 100000 500000 1000000 5000000 10000000)

# Проверка существования программы
check_program() {
    if [ ! -f "$1" ]; then
        echo "Error: Program $1 not found. Ensure it is compiled."
        exit 1
    fi
}

PROGRAM="build/mergesort_sequential"
OUTPUT_FILE="results_sequential.csv"

check_program $PROGRAM
echo "ArraySize,ExecutionTime" > $OUTPUT_FILE

for SIZE in "${ARRAY_SIZES[@]}"; do
    echo "Running sequential mergesort for array size $SIZE..."
    OUTPUT=$($PROGRAM $SIZE)

    # Извлечение времени выполнения
    TIME=$(echo "$OUTPUT" | grep "Execution time:" | awk '{print $3}')

    # Запись результатов
    echo "$SIZE,$TIME" >> $OUTPUT_FILE
done

echo "Sequential results saved to $OUTPUT_FILE"
