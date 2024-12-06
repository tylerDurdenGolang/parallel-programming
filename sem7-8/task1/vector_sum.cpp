#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream> // Для работы с файлом

// Функция для генерации случайного вектора
std::vector<int> generate_vector(int size) {
    std::vector<int> vec(size);
    for (int &val : vec) {
        val = rand() % 100; // Случайные числа от 0 до 99
    }
    return vec;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int ProcRank, ProcNum;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    if (argc < 2) {
        if (ProcRank == 0) {
            std::cerr << "Usage: " << argv[0] << " <vector_size>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int vector_size = std::stoi(argv[1]);
    if (vector_size % ProcNum != 0) {
        if (ProcRank == 0) {
            std::cerr << "Vector size must be divisible by the number of processes." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    srand(time(nullptr) + ProcRank);

    int local_size = vector_size / ProcNum;
    std::vector<int> vec;

    if (ProcRank == 0) {
        vec = generate_vector(vector_size);
    }

    std::vector<int> local_vec(local_size);

    double start_time = MPI_Wtime();

    // Распределяем части вектора между процессами
    MPI_Scatter(vec.data(), local_size, MPI_INT, local_vec.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Вычисляем локальную сумму
    int local_sum = 0;
    for (int val : local_vec) {
        local_sum += val;
    }

    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (ProcRank == 0) {
        double elapsed_time = end_time - start_time;

        // Запись результата в файл
        std::ofstream result_file("vector_sum_results.txt");
        if (result_file.is_open()) {
            result_file << "Global Sum: " << global_sum << "\n";
            result_file << "Elapsed Time: " << elapsed_time << " seconds\n";
            result_file.close();
            std::cout << "Results written to vector_sum_results.txt" << std::endl;
        } else {
            std::cerr << "Error: Could not open file for writing!" << std::endl;
        }

        // Также выводим время выполнения
        std::cout << elapsed_time << std::endl;
    }

    MPI_Finalize();
    return 0;
}
