#include <iostream>
#include <mpi.h>

double* convolve(double* x, double* h, int x_size, int h_size)
{
    int y_size = x_size + h_size - 1;
    double* y = new double[y_size];

    for (int i = 0; i < y_size; i++)
    {
        y[i] = 0;
        for (int j = 0; j < h_size; j++)
        {
            if (i - j >= 0 && i - j < x_size)
            {
                y[i] += x[i - j] * h[j];
            }
        }
    }

    return y;
}

int main(int argc, char* argv[]){

    int rank, size;

    int N = 10;
    int M = 3;

    double* X = new double[N];
    double* H = new double[M];

    

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int per_thread = N / size;

    if (rank == 0){
        // Generating X and H
        for (int i = 0; i < N ; i++)
        {
            X[i] = i;
        }

        for (int i = 0; i < M; i++)
        {
            H[i] = 1.0/3.0;
        }

        
        int remainder = N - per_thread * size;

        for (int i = 0; i < size - 1; i++)
        {
            MPI_Send(&X[i * per_thread], per_thread, MPI_DOUBLE, i+1, 0, MPI_COMM_WORLD);
            MPI_Send(&H[0], M, MPI_DOUBLE, i+1, 1, MPI_COMM_WORLD);
        }

        // for (int i = 0; i < per_thread + remainder; i++)
        // {
        //     std::cout << rank << " : x : " << X[per_thread * (size - 1) + i] << std::endl;
        // }

        double* Y_local = convolve(&X[per_thread * (size - 1)], H, per_thread + remainder, M);

        // for (int i = 0; i < per_thread + remainder + M - 1; i++)
        // {
        //     std::cout << rank << " : y : " << Y_local[i] << std::endl;
        // }

        double* Y = new double[N + M - 1];
        double* Y_recv = new double[per_thread + M - 1];

        for (int i = 0; i < size - 1; i++)
        {
            MPI_Recv(&Y_recv[0], per_thread + M - 1, MPI_DOUBLE, i + 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < per_thread + M - 1; j++)
            {
                Y[i * per_thread + j] += Y_recv[j];
            }
        }

        for (int i = 0; i < per_thread + remainder + M - 1; i++)
        {
            Y[(size - 1) * per_thread + i] += Y_local[i];
        }

        for (int i = 0; i < N + M - 1; i++)
        {
            std::cout << Y[i] << std::endl;
        }

        
    }
    else{
        double* X_local = new double[per_thread];
        double* H_local = new double[M];

        MPI_Recv(&X_local[0], per_thread, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&H_local[0], M, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        // for(int i = 0; i < per_thread; i++){
        //     std::cout << rank << " : x : " << X_local[i] << std::endl;
        // }

        double* Y_local = convolve(X_local, H_local, per_thread, M);

        // for (int i = 0; i < per_thread + M - 1; i++)
        // {
        //     std::cout << rank << " : y : " << Y_local[i] << std::endl;
        // }

        MPI_Send(&Y_local[0], per_thread + M - 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
        
    }


    MPI_Finalize();
}