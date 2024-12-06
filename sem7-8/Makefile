# Папки
BUILD_DIR = build
TASK1_DIR = task1
TASK2_DIR = task2

# Файлы для задач
VECTOR_SUM_SRC = $(TASK1_DIR)/vector_sum.cpp
MATRIX_MUL_SRC = $(TASK2_DIR)/matrix_multiplication.cpp

# Выходные файлы
VECTOR_SUM_EXEC = $(BUILD_DIR)/vector_sum
MATRIX_MUL_EXEC = $(BUILD_DIR)/matrix_multiplication

# Компилятор
CC = mpic++
CFLAGS = -std=c++11 -Wall -Wextra

# Количество процессов для запуска
PROCESSES_SUM = 4
PROCESSES_MUL = 4

# Компиляция всех программ
all: $(BUILD_DIR) $(VECTOR_SUM_EXEC) $(MATRIX_MUL_EXEC)

# Создание папки build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Компиляция программы для задачи 1
$(VECTOR_SUM_EXEC): $(VECTOR_SUM_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(VECTOR_SUM_EXEC) $(VECTOR_SUM_SRC)

# Компиляция программы для задачи 2
$(MATRIX_MUL_EXEC): $(MATRIX_MUL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(MATRIX_MUL_EXEC) $(MATRIX_MUL_SRC)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Запуск задач
run_vector_sum: $(VECTOR_SUM_EXEC)
	mpirun -np $(PROCESSES_SUM) ./$(VECTOR_SUM_EXEC)

run_matrix_mul: $(MATRIX_MUL_EXEC)
	mpirun -np $(PROCESSES_MUL) ./$(MATRIX_MUL_EXEC)

run_all: run_vector_sum run_matrix_mul
