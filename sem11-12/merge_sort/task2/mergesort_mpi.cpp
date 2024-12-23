#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <mpi.h>

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

// Последовательная реализация сортировки слиянием
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
    int remainder = n % size;  // Оставшиеся элементы

    std::vector<int> arr, chunk;

    if (rank == 0) {
        arr.resize(n);
        std::generate(arr.begin(), arr.end(), rand);
    }

    if (rank == size - 1) {
        // Последний процесс получает дополнительные элементы
        chunkSize += remainder;
    }

    chunk.resize(chunkSize);

    // Замер времени начала
    double startTime = MPI_Wtime();

    // Распределение данных между процессами
    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            int startIdx = i * (n / size);
            int sendSize = (i == size - 1) ? chunkSize : n / size;
            MPI_Send(arr.data() + startIdx, sendSize, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        chunk.assign(arr.begin(), arr.begin() + chunkSize);
    } else {
        MPI_Recv(chunk.data(), chunkSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Локальная сортировка
    mergeSort(chunk, 0, chunkSize - 1);

    // Сбор отсортированных частей
    if (rank == 0) {
        std::vector<int> sortedArr(n);
        std::copy(chunk.begin(), chunk.end(), sortedArr.begin());

        for (int i = 1; i < size; ++i) {
            int recvSize = (i == size - 1) ? chunkSize : n / size;
            MPI_Recv(sortedArr.data() + i * (n / size), recvSize, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Слияние всех частей
        for (int step = n / size; step < n; step *= 2) {
            for (int i = 0; i < n; i += 2 * step) {
                int mid = std::min(i + step - 1, n - 1);
                int right = std::min(i + 2 * step - 1, n - 1);
                merge(sortedArr, i, mid, right);
            }
        }

        // Замер времени окончания
        double endTime = MPI_Wtime();

        std::cout << "MPI MergeSort completed.\n";
        std::cout << "Total execution time: " << endTime - startTime << " seconds.\n";
    } else {
        MPI_Send(chunk.data(), chunkSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
