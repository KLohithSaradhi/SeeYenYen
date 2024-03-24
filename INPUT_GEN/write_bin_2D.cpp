#include <iostream>
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


    ofstream writefile(filename, ios::binary);
    writefile.write(reinterpret_cast<char*>(&arr), sizeof(arr));
    writefile.close();


    double** arr2 = new double*[M];

    for (int i = 0; i < M; i++)
    {
        arr2[i] = new double[N];
    }

    ifstream readfile(filename, ios::binary);
    readfile.read(reinterpret_cast<char*>(&arr2), sizeof(arr2));
    readfile.close();

    for (int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}