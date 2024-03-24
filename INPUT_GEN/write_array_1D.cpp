#include <iostream>
#include <math.h>
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


    fstream writefile;
    writefile.open(filename, ios::out);

    for (int i = 0; i < N; i++)
    {
        writefile << arr[i] << endl;
    }

    writefile.close();
}