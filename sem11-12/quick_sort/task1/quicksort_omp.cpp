#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <omp.h>
#include <algorithm>

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

// Параллельная рекурсивная реализация QuickSort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            quickSort(arr, low, pivot - 1);

            #pragma omp section
            quickSort(arr, pivot + 1, high);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <array_size> <num_threads>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    int threads = std::atoi(argv[2]);

    if (n <= 0 || threads <= 0) {
        std::cerr << "Array size and number of threads must be positive.\n";
        return 1;
    }

    std::vector<int> arr(n);
    std::generate(arr.begin(), arr.end(), rand);

    omp_set_num_threads(threads);

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " seconds.\n";

    return 0;
}
