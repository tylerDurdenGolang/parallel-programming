#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <omp.h>

// Функция слияния двух отсортированных частей массива
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Параллельная сортировка слиянием
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, left, mid);

            #pragma omp section
            mergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
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
    mergeSort(arr, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " seconds.\n";

    return 0;
}
