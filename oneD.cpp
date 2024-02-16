#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

double* conv_simple(double* x, double* h, int x_size, int h_size)
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

double* conv_mem_access_eff(double* x, double* h, int x_size, int h_size){
    int y_size = x_size - h_size + 1;
    double* y = new double[y_size];
    int offset;

    if (h_size % 2 == 0)
        offset = h_size - 1;
    else
        offset = h_size - 1;

    int initialised_so_far = 0;

    for (int i = 0; i < x_size; i++){
        for ( int j = max(0, h_size - 1 - i); j < min(h_size, x_size - i);j++){
            if (initialised_so_far < i+j-offset){
                y[i+j - offset] = 0;
                initialised_so_far = i+j - offset;
            }

            y[i+j - offset] += x[i] * h[j];
        }
    }

    return y;

}

double* randomGenerateArray(int size)
{
    double* arr = new double[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 3;
    }

    return arr;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <size of x> <size of h>" << endl;
        return 1;
    }


    int x_n = atoi(argv[1]);
    int h_n = atoi(argv[2]);

    double* x = randomGenerateArray(x_n);

    double* h = randomGenerateArray(h_n);

    auto start = chrono::high_resolution_clock::now();

    double* y_simple = conv_simple(x, h, x_n, h_n);

    auto end = chrono::high_resolution_clock::now();

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    start = chrono::high_resolution_clock::now();

    double* y_eff = conv_mem_access_eff(x, h, x_n, h_n);

    end = chrono::high_resolution_clock::now();

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    if (x_n < 10){
        for (int i = 0; i < x_n; i++){
            cout << x[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < h_n; i++){
            cout << h[i] << " ";
        }
        cout << endl;


        for (int i = 0; i < (x_n + h_n  - 1); i++)
        {
            cout << y_simple[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < (x_n - h_n  + 1); i++)
        {
            cout << y_eff[i] << " ";
        }
        cout << endl;
    }
}