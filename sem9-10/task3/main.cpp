#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h> // Подключение MPI

void solve_system_mpi(double* Matrix, int m, int n, double eps, int rank, int size) {
    int rows_per_proc = n / size; // Число строк на процесс
    int start_row = rank * rows_per_proc;
    int end_row = (rank == size - 1) ? n : start_row + rows_per_proc;

    double dmax;
    do {
        dmax = 0.0;
        for (int i = start_row; i < end_row; i++) {
            for (int j = 1; j < m - 1; j++) {
                int idx = i * m + j;
                double temp = Matrix[idx];
                Matrix[idx] = 0.25 * (Matrix[idx - 1] + Matrix[idx + 1] + Matrix[idx - m] + Matrix[idx + m]);
                double dm = fabs(temp - Matrix[idx]);
                if (dm > dmax) dmax = dm;
            }
        }

        // Обмен граничными значениями между процессами
        if (rank > 0) {
            MPI_Send(Matrix + start_row * m, m, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(Matrix + (start_row - 1) * m, m, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Recv(Matrix + end_row * m, m, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(Matrix + (end_row - 1) * m, m, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
        }

        // Сбор максимального изменения среди всех процессов
        double global_dmax;
        MPI_Allreduce(&dmax, &global_dmax, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
        dmax = global_dmax;
    } while (dmax > eps);
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 3) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <grid_size> <epsilon>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int n = std::atoi(argv[1]);
    double eps = std::atof(argv[2]);
    int m = n;

    std::vector<double> Matrix(n * n, 0.0);
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            Matrix[i] = 1.0;
            Matrix[i * n] = 1.0;
        }
    }

    MPI_Bcast(Matrix.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();
    solve_system_mpi(Matrix.data(), m, n, eps, rank, size);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        std::cout << "Execution time: " << (end_time - start_time) << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
