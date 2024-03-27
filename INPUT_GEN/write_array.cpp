#include <iostream>
#include <math.h>
#include <fstream>
#include <cereal/archives/binary.hpp>

using namespace std;

int main(int argc, char* argv[]){
    int N = stoi(argv[1]);
    char* filename = argv[2];

    N = pow(N, 2);
    double* arr = new double[N];

    cout << N << endl;

    int MAXRAND = 100000;
    int LOWER = 0;
    int UPPER = 100;
    for (int i = 0; i < N; i++)
    {
        arr[i] = LOWER + (UPPER - LOWER) * ((double)(rand() % MAXRAND) / (double)MAXRAND);
    }


    ofstream write_file(filename, std::ios::binary);
    cereal::BinaryOutputArchive archive( write_file );

    archive( cereal::binary_data( arr, sizeof(double) * N ) );
    
}