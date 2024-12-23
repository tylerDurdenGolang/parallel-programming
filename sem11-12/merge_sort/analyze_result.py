import pandas as pd
import matplotlib.pyplot as plt
import argparse

# Парсинг аргументов командной строки
parser = argparse.ArgumentParser(description="Analyze results for OpenMP or MPI")
parser.add_argument('--mode', choices=['openmp', 'mpi'], required=True, help="Choose between OpenMP and MPI")
args = parser.parse_args()
# Пути к CSV-файлам
sequential_file = "results_sequential.csv"
mpi_file = "results_mpi.csv"
openmp_file = "results_openmp.csv"
sequential_results = pd.read_csv(sequential_file).set_index('ArraySize')

if args.mode == 'mpi':
    parallel_results = pd.read_csv(mpi_file).pivot(index='ArraySize', columns='Processes', values='ExecutionTime')
elif args.mode == 'openmp':
    parallel_results = pd.read_csv(openmp_file).pivot(index='ArraySize', columns='Threads', values='ExecutionTime')

# Создание таблицы
table = pd.DataFrame({
    "Количество элементов": sequential_results.index,
    "Последовательный алгоритм (время, сек)": sequential_results['ExecutionTime'],
    "2 процесса (время, сек)": parallel_results[2],
    "2 процесса (ускорение)": sequential_results['ExecutionTime'] / parallel_results[2],
    "4 процесса (время, сек)": parallel_results[4],
    "4 процесса (ускорение)": sequential_results['ExecutionTime'] / parallel_results[4],
    "8 процессов (время, сек)": parallel_results[8],
    "8 процессов (ускорение)": sequential_results['ExecutionTime'] / parallel_results[8],
})

# Построение графиков ускорения
def plot_speedup(table, title, filename):
    plt.figure(figsize=(12, 6))
    
    # Построение ускорения
    plt.plot(table["Количество элементов"], table["2 процесса (ускорение)"], marker='o', label="2 процесса")
    plt.plot(table["Количество элементов"], table["4 процесса (ускорение)"], marker='o', label="4 процесса")
    plt.plot(table["Количество элементов"], table["8 процессов (ускорение)"], marker='o', label="8 процессов")
    
    plt.title(title)
    plt.xlabel("Количество элементов")
    plt.ylabel("Ускорение")
    plt.xscale("log")
    plt.grid(True)
    plt.legend()
    plt.savefig(filename)
    plt.close()

# Построение графиков времени выполнения
def plot_execution_time(table, title, filename):
    plt.figure(figsize=(12, 6))
    
    # Построение времени выполнения
    plt.plot(table["Количество элементов"], table["Последовательный алгоритм (время, сек)"], marker='o', label="Последовательный")
    plt.plot(table["Количество элементов"], table["2 процесса (время, сек)"], marker='o', label="2 процесса")
    plt.plot(table["Количество элементов"], table["4 процесса (время, сек)"], marker='o', label="4 процесса")
    plt.plot(table["Количество элементов"], table["8 процессов (время, сек)"], marker='o', label="8 процессов")
    
    plt.title(title)
    plt.xlabel("Количество элементов")
    plt.ylabel("Время выполнения (секунды)")
    plt.xscale("log")
    plt.yscale("log")
    plt.grid(True)
    plt.legend()
    plt.savefig(filename)
    plt.close()
    
# Сохранение таблицы в Excel
output_file = f"{args.mode}_results/final_results_{args.mode}_table.xlsx"
table.to_excel(output_file, index=False)
# Построение графиков
plot_speedup(table, f"Ускорение {args.mode.upper()}", f"{args.mode}_results/{args.mode}_speedup.png")
plot_execution_time(table, f"Время выполнения {args.mode.upper()}", f"{args.mode}_results/{args.mode}_execution_time.png")

# Вывод таблицы и сообщения
print(table)
print(f"Графики сохранены как {args.mode}_speedup.png и {args.mode}_execution_time.png")
