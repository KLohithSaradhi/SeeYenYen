#include <fstream>
#include <iostream>
// #include <mpi.h>

using namespace std;


int main(int argc, char* argv[]){

    int X_N = stoi(argv[1]);
    int H_N = stoi(argv[3]);


    char* X_file = argv[2];
    char* H_file = argv[4];

    cout << X_N << " " << H_N << endl;
    cout << X_file << " " << H_file << endl;

    X_N = pow(2, X_N);
    H_N = pow(2, H_N);

    double* X = new double[X_N];
    double* H = new double[H_N];

    cout << X_N << " " << H_N << endl;
    cout << sizeof(X) << " " << sizeof(H) << endl;


    cout << "here\n";

    ifstream X_read(X_file, ios::binary);
    X_read.read(reinterpret_cast<char*>(&X), sizeof(X));
    X_read.close();

    cout << "X_read\n";

    ifstream H_read(H_file, ios::binary);
    H_read.read(reinterpret_cast<char*>(&H), sizeof(H));
    H_read.close();

    cout << "H_read\n";

    cout << X[0] << endl;

    cout << endl;


    for (int i = 0; i < H_N; i++)
    {
        cout << H[i] << " ";
    }

    cout << endl;

}