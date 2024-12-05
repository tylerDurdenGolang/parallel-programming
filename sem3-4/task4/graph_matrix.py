import pandas as pd
import matplotlib.pyplot as plt

# Чтение данных из CSV
data = pd.read_csv('block_matrix_results_optimized.csv')  # Замените на ваш путь к CSV-файлу

# Уникальные размеры матриц, потоки и размеры блоков
matrix_sizes = sorted(data['MatrixSize'].unique())
threads = sorted(data['Threads'].unique())
block_sizes = sorted(data['BlockSize'].unique())

# Построение графиков
plt.figure(figsize=(14, 8))
for block_size in block_sizes:
    for thread in threads:
        # Фильтрация данных для текущего количества потоков и размера блока
        subset = data[(data['Threads'] == thread) & (data['BlockSize'] == block_size)]

        # Построение графика
        plt.plot(subset['MatrixSize'], subset['ExecutionTime'],
                 label=f'Блок {block_size}, {thread} потока(-ов)', marker='o')

# Оформление графика
plt.title('Производительность блочного умножения матриц', fontsize=16)
plt.xlabel('Размер матрицы (число строк)', fontsize=14)
plt.ylabel('Время выполнения (секунды)', fontsize=14)
plt.legend(fontsize=10, loc='upper left', bbox_to_anchor=(1, 1))
plt.grid(True)
plt.tight_layout()

# Сохранение графика в файл
plt.savefig('performance_plot.png')

# Отображение графика
plt.show()
