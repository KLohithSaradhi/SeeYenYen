#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

double** conv_simple(double** x, double** h, int x_size, int h_size)
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

double** conv_mem_access_eff(double** x, double** h, int x_size, int h_size){
    int y_size = x_size - h_size + 1;
    double** y = new double*[y_size];

    for (int i = 0; i < y_size; i++){
        y[i] = new double[y_size];
        for (int j = 0; j < y_size; j ++){
            y[i][j] = 0;
        }
    }

    int offset;
    if (h_size % 2 == 0)
        offset = h_size - 1;
    else
        offset = h_size - 1;

    for(int i = 0; i < x_size; i++){
        for (int j = 0; j < x_size; j++){

            for (int k = max(0, h_size - 1 -i); k < min(h_size, x_size - i);k++){
                for (int l = max(0, h_size - 1 -j); l < min(h_size, x_size - j);l++){
                    y[i+k-offset][j+l-offset] += x[i][j] * h[k][l];
                }
            }

        }
    }

    return y;
    
}

double** generate_random(int size){
    double** arr = new double*[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = rand() % 10;
        }
    }

    return arr;
}

int main(int argc, char* argv[]){

    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <size of x> <size of h>" << endl;
        return 1;
    }

    int x_size = atoi(argv[1]);
    int h_size = atoi(argv[2]);

    double **x = generate_random(x_size);
    double **h = generate_random(h_size);


    int y_size = x_size - h_size + 1;

    auto start = chrono::high_resolution_clock::now();

    double** y = conv_simple(x, h, x_size, h_size);

    auto end = chrono::high_resolution_clock::now();

    cout << "Simple Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    start = chrono::high_resolution_clock::now();

    y = conv_mem_access_eff(x, h, x_size, h_size);

    end = chrono::high_resolution_clock::now();

    cout << "Mem_access Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    

    if (x_size < 10){
        for (int i=0; i < x_size;i++){
            for (int j=0; j < x_size;j++){
                cout << x[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;

        for (int i=0; i < h_size;i++){
            for (int j=0; j < h_size;j++){
                cout << h[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;

        for (int i=0; i < y_size;i++){
            for (int j=0; j < y_size;j++){
                cout << y[i][j] << " ";
            }
            cout << endl;
        }
    }

    cout << endl;
}