#!/bin/bash

# Очистка старых файлов результатов
rm -f results_summary_*.csv

# Параметры экспериментов
GRID_SIZES=(10 100 1000 2000 3000)
EPSILON=0.0001
MPI_PROCESSES=(2 4) # Количество процессов для MPI

# Проверка существования программы
check_program() {
    if [ ! -f "$1" ]; then
        echo "Error: Program $1 not found. Ensure it is compiled."
        exit 1
    fi
}

# Функция для запуска последовательной версии
run_sequential() {
    PROGRAM="build/solve_system"
    OUTPUT_FILE="results_summary_sequential.csv"

    check_program $PROGRAM
    echo "GridSize,ExecutionTime" > $OUTPUT_FILE

    for GRID in "${GRID_SIZES[@]}"; do
        echo "Running sequential for grid size $GRID..."
        OUTPUT=$($PROGRAM $GRID $EPSILON)

        # Извлечение времени выполнения
        TIME=$(echo "$OUTPUT" | while read -r line; do
            if [[ $line == Execution\ time:* ]]; then
                echo "${line#Execution time: }" | cut -d' ' -f1
            fi
        done)

        # Запись результатов
        echo "$GRID,$TIME" >> $OUTPUT_FILE
    done

    echo "Sequential results saved to $OUTPUT_FILE"
}

# Функция для запуска OpenMP версии
run_openmp() {
    PROGRAM="build/solve_system_omp"
    OUTPUT_FILE="results_summary_openmp.csv"

    check_program $PROGRAM
    echo "GridSize,Threads,ExecutionTime" > $OUTPUT_FILE

    THREADS=(2 4 6) # Количество потоков для тестирования

    for GRID in "${GRID_SIZES[@]}"; do
        for THREAD in "${THREADS[@]}"; do
            echo "Running OpenMP for grid size $GRID with $THREAD threads..."
            OUTPUT=$($PROGRAM $GRID $EPSILON $THREAD)

            # Извлечение времени выполнения
            TIME=$(echo "$OUTPUT" | while read -r line; do
                if [[ $line == Execution\ time:* ]]; then
                    echo "${line#Execution time: }" | cut -d' ' -f1
                fi
            done)

            # Запись результатов
            echo "$GRID,$THREAD,$TIME" >> $OUTPUT_FILE
        done
    done

    echo "OpenMP results saved to $OUTPUT_FILE"
}

# Функция для запуска MPI версии
run_mpi() {
    PROGRAM="build/solve_system_mpi"
    OUTPUT_FILE="results_summary_mpi.csv"

    check_program $PROGRAM
    echo "GridSize,Processes,ExecutionTime" > $OUTPUT_FILE

    for GRID in "${GRID_SIZES[@]}"; do
        for PROC in "${MPI_PROCESSES[@]}"; do
            echo "Running MPI for grid size $GRID with $PROC processes..."
            OUTPUT=$(mpirun --oversubscribe -np $PROC $PROGRAM $GRID $EPSILON)

            # Извлечение времени выполнения
            TIME=$(echo "$OUTPUT" | while read -r line; do
                if [[ $line == Execution\ time:* ]]; then
                    echo "${line#Execution time: }" | cut -d' ' -f1
                fi
            done)

            # Запись результатов
            echo "$GRID,$PROC,$TIME" >> $OUTPUT_FILE
        done
    done

    echo "MPI results saved to $OUTPUT_FILE"
}

# Запуск всех экспериментов
# run_sequential
run_openmp
run_mpi

echo "All experiments completed."
