#include <iostream>
#include <vector>

using namespace std;

double* conv(double* x, double* h, int x_size, int h_size)
{
    int y_size = x_size + h_size - 1;
    double* y = new double[y_size];

    for (int i = 0; i < y_size; i++)
    {
        y[i] = 0;
        for (int j = 0; j < h_size; j++)
        {
            if (i - j >= 0 && i - j < x_size)
            {
                y[i] += x[i - j] * h[j];
            }
        }
    }

    return y;
}

double* randomGenerateArray(int size)
{
    double* arr = new double[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 1000;
    }

    return arr;
}

int main()
{
    int x_n = 100000;
    int h_n = 1000;

    double* x = randomGenerateArray(x_n);

    double* h = randomGenerateArray(h_n);

    double* y = conv(x, h, x_n, h_n);

    for (int i = 0; i < (x_n + h_n  - 1); i++)
    {
        cout << y[i] << endl;
    }
}