#include <iostream>
#include <vector>

using namespace std;

double** conv(double** x, double** h, int x_size, int h_size)
{
    int y_size = x_size - h_size + 1;
    double** y = new double*[y_size];

    int half_size = h_size / 2;

    for (int i = 0; i < y_size; i++)
    {
        y[i] = new double[y_size];
        for (int j = 0; j < y_size; j++)
        {
            y[i][j] = 0;
            for (int k = 0; k < h_size; k++)
            {
                for (int l = 0; l < h_size; l++)
                {
                    if (i + k < x_size && j + l < x_size)
                    {
                        y[i][j] += x[i + k][j + l] * h[h_size - k - 1][h_size - l - 1];
                    }
                }
            }
        }
    }


    return y;
}

int main(){

    cout << "hoi" << endl;

    double* x[9];
    double* h[5];

    for (int i=0; i < 9;i++){
        x[i] = new double[9];
    }

    for (int i=0; i < 5;i++){
        h[i] = new double[5];
    }

    for (int i=0; i < 9;i++){
        for (int j=0; j < 9;j++){
            x[i][j] = 0;
            if (i == 4 && j == 4){
                x[i][j] = 1;
            }
        }
    }

    for (int i=0; i < 5;i++){
        for (int j=0; j < 5;j++){
            h[i][j] = 0;
            if (j == 1){
                h[i][j] = 1;
            }
        }
    }

    for (int i=0; i < 9;i++){
        for (int j=0; j < 9;j++){
            cout << x[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i=0; i < 5;i++){
        for (int j=0; j < 5 ;j++){
            cout << h[i][j] << " ";
        }
        cout << endl;
    }


    double** y = conv(x, h, 9, 5);

    cout << endl;

    for (int i=0; i < 5;i++){
        for (int j=0; j < 5;j++){
            cout << y[i][j] << " ";
        }
        cout << endl;
    }

}