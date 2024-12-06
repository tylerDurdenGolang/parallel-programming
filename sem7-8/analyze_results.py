import pandas as pd
import matplotlib.pyplot as plt

# Чтение данных из CSV
data = pd.read_csv("vector_results.csv")

# Проверка, что нужные столбцы существуют
if not {"Processes", "ExecutionTime"}.issubset(data.columns):
    raise ValueError("CSV файл должен содержать столбцы 'Processes' и 'ExecutionTime'.")

# Построение графика
plt.figure(figsize=(10, 6))
plt.plot(data["Processes"], data["ExecutionTime"], marker='o', linestyle='-', label="Execution Time")

# Настройки графика
plt.title("Зависимость времени выполнения от числа процессов", fontsize=14)
plt.xlabel("Количество процессов", fontsize=12)
plt.ylabel("Время выполнения (секунды)", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend(fontsize=12)

# Сохранение и показ графика
plt.tight_layout()
plt.savefig("processes_vs_execution_time.png", dpi=300)
plt.show()
