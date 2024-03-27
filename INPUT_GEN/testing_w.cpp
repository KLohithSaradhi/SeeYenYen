#include <iostream>
#include <fstream>
#include <cereal/archives/binary.hpp>

using namespace std;

int main(int argc, char* argv[]){

    double arr[3] = {1.0, 2.0, 3.0};


    ofstream write_file("out.bin", std::ios::binary);
    cereal::BinaryOutputArchive archive( write_file );

    archive( cereal::binary_data( arr, sizeof(double) * 3 ) );
}