#include <iostream>
#include <mpi.h>
#include <math.h>
#include <fstream>
#include <cereal/archives/binary.hpp>

using namespace std;

double** convolve(double** x, double** h, int x_n, int x_m, int h_n, int h_m)
{
    int y_n = x_n + h_n - 1;
    int y_m = x_m + h_m - 1;
    double** y = new double*[y_n];


    for (int i = 0; i < y_n; i++)
    {
        y[i] = new double[y_m];
        for (int j = 0; j < y_m; j++)
        {
            y[i][j] = 0;
            for (int k = 0; k < h_n; k++)
            {
                for (int l = 0; l < h_m; l++)
                {
                    if (i - k >= 0 && j - l >= 0 && i - k < x_n && j - l < x_m)
                    {
                        y[i][j] += x[i - k][j - l] * h[k][l];
                    }
                }
            }
        }
    }

    return y;
}

int main(int argc, char* argv[]){
    int rank, size;

    int N = stoi(argv[1]);
    int M = stoi(argv[3]);
    char* X_file = argv[2];
    char* H_file = argv[4];


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int per_thread = N / size;

    if (rank == 0){

        // reading from X.bin and H.bin
        

        double* X_linear = new double[N * N];
        double* H_linear = new double[M * M];

        ifstream X_read_file(X_file, std::ios::binary);

        {
        cereal::BinaryInputArchive archive( X_read_file );
        archive( cereal::binary_data( X_linear, sizeof(double) * N * N ) );
        }

        ifstream H_read_file(H_file, std::ios::binary);
        {
        cereal::BinaryInputArchive archive( H_read_file );
        archive( cereal::binary_data( H_linear, sizeof(double) * M * M ) );
        }



        // Writing to X and H
        double** X = new double*[N];
        double** H = new double*[M];
        for (int i = 0; i < N; i++)
        {
            X[i] = new double[N];
            for (int j = 0; j < N; j++)
            {
                X[i][j] = X_linear[i * N + j];
            }
        }
        for (int i = 0; i < M; i++)
        {
            H[i] = new double[M];
            for (int j = 0; j < M; j++)
            {
                H[i][j] = H_linear[i * M + j];
            }
        }

        

        // Input is 2 power something
        
        int remainder = N - per_thread * size;

        for (int i = 0; i < size - 1; i++)
        {
            MPI_Send(&(X[i * per_thread][0]), per_thread * N, MPI_DOUBLE, i+1, 0, MPI_COMM_WORLD);
            MPI_Send(&(H[0][0]), M * M, MPI_DOUBLE, i+1, 1, MPI_COMM_WORLD);
        }

        double** Y = new double*[N + M - 1];
        for (int i = 0; i < N + M - 1; i++)
        {
            Y[i] = new double[N + M - 1];
            for (int j = 0; j < N + M - 1; j++)
            {
                Y[i][j] = 0;
            }
        }

        double* Y_local = new double[(per_thread + M - 1) * (N + M - 1)];

        double** Y_out = convolve(&X[(size - 1)*per_thread], H, per_thread, N, M, M);
        

        for (int thread = 0; thread < size - 1; thread++){
            MPI_Recv(&(Y_local[0]), (per_thread + M - 1) * (N + M - 1), MPI_DOUBLE, thread+1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


            for (int i = 0; i < per_thread + M - 1; i++)
            {
                for (int j = 0; j < N + M - 1; j++)
                {
                    Y[(thread) * per_thread + i][j] += Y_local[i * (N + M - 1) + j];
                }
            }
        }

        for (int i = 0; i < per_thread + M - 1; i++){
            for (int j = 0; j < N + M - 1; j++){
                Y[(size - 1) * per_thread + i][j] += Y_out[i][j];
            }
        }

        for (int i = 0; i < N + M - 1 ; i++)
        {
            for (int j = 0; j < N + M - 1; j++)
            {
                cout << Y[i][j] << " ";
            }
            cout << endl;
        }
    }
    else{
        double* X_local = new double[per_thread * N];
        MPI_Recv(X_local, per_thread * N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double* H_local = new double[M * M];
        MPI_Recv(H_local, M * M, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double** X = new double*[per_thread];
        for (int i = 0; i < per_thread; i++)
        {
            X[i] = new double[N];
            for (int j = 0; j < N; j++)
            {
                X[i][j] = X_local[i * N + j];
            }
        }

        free(X_local);

        double** H = new double*[M];
        for (int i = 0; i < M; i++)
        {
            H[i] = new double[M];
            for (int j = 0; j < M; j++)
            {
                H[i][j] = H_local[i * M + j];
            }
        }

        double** Y = convolve(X, H, per_thread, N, M, M);
        MPI_Send(&(Y[0][0]), (per_thread + M - 1) * (N + M - 1), MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
        

    }


    MPI_Finalize();


}