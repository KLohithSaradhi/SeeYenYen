#include <mpi.h>
#include <iostream>
#include <math.h>

using namespace std;

double* randomGenerateArray(int size)
{
    double* arr = new double[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 3;
    }

    return arr;
}

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        int x_size = pow(2, 15);
        int h_size = 13;

        double* x = randomGenerateArray(x_size);
        double* h = randomGenerateArray(h_size);

        
    }

    MPI_Finalize();
}