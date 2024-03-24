#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    int M = stoi(argv[1]);
    int N = stoi(argv[2]);
    char* filename = argv[3];

    M = pow(2, M);
    N = pow(2, N);
    

    double** arr = new double*[M];
    for (int i = 0; i < M; i++)
    {
        arr[i] = new double[N];
    }
    


    int MAXRAND = 100000;
    int LOWER = 0;
    int UPPER = 100;
    for (int i = 0; i < M; i++)
    {   
        for (int j = 0; j < N; j++){
            arr[i][j] = LOWER + (UPPER - LOWER) * ((double)(rand() % MAXRAND) / (double)MAXRAND);
        }
    }


    fstream writefile;
    writefile.open(filename, ios::out);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++){
            writefile << arr[j][i] << " ";
        }
        writefile << endl;
    }

    writefile.close();
}