import pandas as pd
import matplotlib.pyplot as plt

# Чтение данных из CSV
data = pd.read_csv('gauss_results.csv')  # Замените на путь к вашему CSV-файлу

# Уникальные размеры матриц и потоки
matrix_sizes = sorted(data['MatrixSize'].unique())
threads = [3, 4]  # Только два значения потоков

# Построение графиков
plt.figure(figsize=(10, 6))
for size in matrix_sizes:
    # Фильтрация данных для текущего размера матрицы
    subset = data[data['MatrixSize'] == size]

    # Построение графика
    plt.plot(subset['Threads'], subset['ExecutionTime'], label=f'Размер матрицы {size}', marker='o')

# Оформление графика
plt.title('Производительность метода Гаусса (3 и 4 потока)', fontsize=16)
plt.xlabel('Количество потоков', fontsize=14)
plt.ylabel('Время выполнения (секунды)', fontsize=14)
plt.xticks(threads)  # Установка меток для оси X
plt.legend(fontsize=12)
plt.grid(True)
plt.tight_layout()

# Сохранение графика в файл
plt.savefig('gauss_performance_plot_limited_threads.png')

# Отображение графика
plt.show()
