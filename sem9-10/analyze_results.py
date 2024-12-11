import pandas as pd
import matplotlib.pyplot as plt

# Load data
sequential_file = "task1/results_summary.csv"
mpi_file = "task3/results_summary_mpi.csv"
openmp_file = "task2/results_summary_openmp.csv"

# Load data into dataframes
sequential_results = pd.read_csv(sequential_file).set_index('GridSize')
mpi_results = pd.read_csv(mpi_file)
openmp_results = pd.read_csv(openmp_file)

# Prepare MPI data
mpi_pivot = mpi_results.pivot(index='GridSize', columns='Processes', values='ExecutionTime')
mpi_speedup = mpi_pivot.divide(sequential_results['ExecutionTime'], axis=0)

# Prepare OpenMP data
openmp_pivot = openmp_results.pivot(index='GridSize', columns='Threads', values='ExecutionTime')
openmp_speedup = openmp_pivot.divide(sequential_results['ExecutionTime'], axis=0)

# Generate MPI table
mpi_table = pd.DataFrame({
    "Размер сетки": sequential_results.index,
    "Последовательный алгоритм (время, сек)": sequential_results['ExecutionTime'],
    "2 процесса (время, сек)": mpi_pivot[2],
    "2 процесса (ускорение)": mpi_speedup[2],
    "4 процесса (время, сек)": mpi_pivot[4],
    "4 процесса (ускорение)": mpi_speedup[4],
    "6 процессов (время, сек)": mpi_pivot[6],
    "6 процессов (ускорение)": mpi_speedup[6],
})

# Generate OpenMP table
openmp_table = pd.DataFrame({
    "Размер сетки": sequential_results.index,
    "Последовательный алгоритм (время, сек)": sequential_results['ExecutionTime'],
    "2 потока (время, сек)": openmp_pivot[2],
    "2 потока (ускорение)": openmp_speedup[2],
    "4 потока (время, сек)": openmp_pivot[4],
    "4 потока (ускорение)": openmp_speedup[4],
    "6 потоков (время, сек)": openmp_pivot[6],
    "6 потоков (ускорение)": openmp_speedup[6],
})

# Save tables to Excel
output_excel = "results_comparison.xlsx"
with pd.ExcelWriter(output_excel) as writer:
    mpi_table.to_excel(writer, sheet_name="MPI Results", index=False)
    openmp_table.to_excel(writer, sheet_name="OpenMP Results", index=False)

# Plot Execution Time Comparison for MPI
plt.figure(figsize=(12, 6))
plt.plot(sequential_results.index, sequential_results['ExecutionTime'], marker='o', label='Последовательный', linewidth=2)
for processes in mpi_pivot.columns:
    plt.plot(mpi_pivot.index, mpi_pivot[processes], marker='o', label=f'MPI {processes} процессов')

plt.title("Время выполнения: Последовательный и MPI")
plt.xlabel("Размер сетки")
plt.ylabel("Время выполнения (с)")
plt.legend()
plt.grid(True)
plt.savefig("mpi_execution_time_comparison.png")
plt.close()

# Plot Execution Time Comparison for OpenMP
plt.figure(figsize=(12, 6))
plt.plot(sequential_results.index, sequential_results['ExecutionTime'], marker='o', label='Последовательный', linewidth=2)
for threads in openmp_pivot.columns:
    plt.plot(openmp_pivot.index, openmp_pivot[threads], marker='o', label=f'OpenMP {threads} потоков')

plt.title("Время выполнения: Последовательный и OpenMP")
plt.xlabel("Размер сетки")
plt.ylabel("Время выполнения (с)")
plt.legend()
plt.grid(True)
plt.savefig("openmp_execution_time_comparison.png")
plt.close()

print("Tables saved to", output_excel)
print("Graphs saved as images.")