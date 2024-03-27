#include <iostream>
#include <fstream>
#include <cereal/archives/binary.hpp>

using namespace std;

int main(int argc, char* argv[]){

    double arr[9];
    for (int i = 0; i < 9; i++)
    {
        arr[i] = (double)i;
    }

    ofstream write_file("out.bin", std::ios::binary);
    cereal::BinaryOutputArchive archive( write_file );

    archive( cereal::binary_data( arr, sizeof(double) * 9 ) );
}