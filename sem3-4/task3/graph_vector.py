import pandas as pd
import matplotlib.pyplot as plt

# Чтение данных из CSV
data = pd.read_csv('results.csv')

# Уникальные размеры матриц и количество потоков
matrix_sizes = sorted(data['MatrixSize'].unique())
threads = sorted(data['Threads'].unique())

# Построение графиков
plt.figure(figsize=(10, 6))
for thread in threads:
    # Фильтрация данных для текущего количества потоков
    thread_data = data[data['Threads'] == thread]

    # Построение для случайных значений
    plt.plot(thread_data['MatrixSize'], thread_data['RandomValuesTime'], 
             label=f'Случайные, {thread} потока(-ов)', linestyle='-', marker='o')

    # Построение для линейных значений
    plt.plot(thread_data['MatrixSize'], thread_data['LinearValuesTime'], 
             label=f'Линейные, {thread} потока(-ов)', linestyle='--', marker='x')

# Оформление графика
plt.title('Производительность умножения матрицы на вектор', fontsize=14)
plt.xlabel('Размер матрицы (число строк)', fontsize=12)
plt.ylabel('Время выполнения (секунды)', fontsize=12)
plt.legend(fontsize=10)
plt.grid(True)
plt.tight_layout()

# Сохранение графика в файл
plt.savefig('performance_plot.png')

# Отображение графика
plt.show()
