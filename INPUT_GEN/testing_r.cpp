#include <iostream>
#include <fstream>
#include <cereal/archives/binary.hpp>

using namespace std;

int main(int argc, char* argv[]){

    double arr[3];


    ifstream read_file("out.bin", std::ios::binary);
    cereal::BinaryInputArchive archive( read_file );

    archive( cereal::binary_data( arr, sizeof(double) * 3 ) );

    for (int i = 0; i < 3; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}