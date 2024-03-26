#include <iostream>

using namespace std;

double** convolve(double** x, double** h, int x_n, int x_m, int h_n, int h_m)
{
    int y_n = x_n + h_n - 1;
    int y_m = x_m + h_m - 1;
    double** y = new double*[y_n];


    for (int i = 0; i < y_n; i++)
    {
        y[i] = new double[y_m];
        for (int j = 0; j < y_m; j++)
        {
            y[i][j] = 0;
            for (int k = 0; k < h_n; k++)
            {
                for (int l = 0; l < h_m; l++)
                {
                    if (i - k >= 0 && j - l >= 0 && i - k < x_n && j - l < x_m)
                    {
                        y[i][j] += x[i - k][j - l] * h[k][l];
                    }
                }
            }
        }
    }

    return y;
}


int main(int argc, char* argv[]){
    int X_N = 8;
    int X_M = 8;

    double** X = new double* [X_N];

    for (int i = 0; i < X_N; i++)
    {
        X[i] = new double[X_M];
        for (int j = 0; j < X_M; j++)
        {
            X[i][j] = i + j;
        }
    }

    

    int H_N = 3;
    int H_M = 3;

    double** H = new double* [H_N];

    for (int i = 0; i < H_N; i++)
    {
        H[i] = new double[H_M];
        for (int j = 0; j < H_M; j++)
        {
            H[i][j] = 1.0/9.0;
        }
    }

    

    double** Y = convolve(X, H, X_N, X_M, H_N, H_M);

    for (int i = 0; i < X_N + H_N - 1; i++)
    {
        for (int j = 0; j < X_M + H_M - 1; j++)
        {
            cout << Y[i][j] << " ";
        }
        cout << endl;
    }



}