#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <mpi.h>

// Разделение массива для QuickSort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Последовательная реализация QuickSort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) std::cerr << "Usage: " << argv[0] << " <array_size>\n";
        MPI_Finalize();
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        if (rank == 0) std::cerr << "Array size must be positive.\n";
        MPI_Finalize();
        return 1;
    }

    int chunkSize = n / size;
    std::vector<int> arr, chunk(chunkSize);

    if (rank == 0) {
        arr.resize(n);
        std::generate(arr.begin(), arr.end(), rand);
    }

    // Начало измерения времени
    double startTime = MPI_Wtime();

    MPI_Scatter(arr.data(), chunkSize, MPI_INT, chunk.data(), chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Локальная сортировка
    std::sort(chunk.begin(), chunk.end());

    MPI_Gather(chunk.data(), chunkSize, MPI_INT, arr.data(), chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Слияние отсортированных частей
    if (rank == 0) {
        for (int step = chunkSize; step < n; step *= 2) {
            for (int i = 0; i < n; i += 2 * step) {
                int mid = i + step - 1;
                int right = std::min(i + 2 * step - 1, n - 1);
                std::inplace_merge(arr.begin() + i, arr.begin() + mid + 1, arr.begin() + right + 1);
            }
        }
    }

    // Конец измерения времени
    double endTime = MPI_Wtime();

    if (rank == 0) {
        std::cout << "Execution time: " << endTime - startTime << " seconds.\n";
    }

    MPI_Finalize();
    return 0;
}
