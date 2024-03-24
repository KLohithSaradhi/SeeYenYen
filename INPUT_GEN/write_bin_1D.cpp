#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    int N = stoi(argv[1]);
    char* filename = argv[2];

    N = pow(2, N);
    double* arr = new double[N];


    int MAXRAND = 100000;
    int LOWER = 0;
    int UPPER = 100;
    for (int i = 0; i < N; i++)
    {
        arr[i] = LOWER + (UPPER - LOWER) * ((double)(rand() % MAXRAND) / (double)MAXRAND);
    }

    ofstream writefile(filename, ios::binary);
    writefile.write(reinterpret_cast<char*>(&arr), sizeof(arr));
    writefile.close();


    double* arr2 = new double[N];

    ifstream readfile(filename, ios::binary);
    readfile.read(reinterpret_cast<char*>(&arr2), sizeof(arr2));
    readfile.close();

    for (int i = 0; i < N; i++)
    {
        cout << arr2[i] << endl;
    }
}