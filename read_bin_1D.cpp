#include <iostream>
#include <fstream>
#include <cereal/archives/binary.hpp>

using namespace std;

int main(int argc, char* argv[]){

    int N = stoi(argv[1]);
    char* filename = argv[2];

    N = pow(N, 2);
    double* arr = new double[N];

    ifstream read_file(filename, std::ios::binary);
    cereal::BinaryInputArchive archive( read_file );

    archive( cereal::binary_data( arr, sizeof(double) * N ) );

    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }

}