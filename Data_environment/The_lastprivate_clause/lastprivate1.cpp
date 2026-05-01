#include <iostream>
#include <omp.h>
using namespace std;

void lastpriv(int n, float *a, float *b)
{
    int i;

    #pragma omp parallel
    {
            #pragma omp for lastprivate(i)
            for(i = 0; i<n-1; i++){
                a[i] = b[i] + b[i+1];
            }

        #pragma omp single
        a[i] = b[i];
    }
}

int main(){
    const int n = 5;
    float a[n] = {0};
    float b[n] = {1, 2, 3, 4, 5};

    lastpriv(n, a, b);

    cout << "数组 b 的值：";
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;

    cout << "数组 a 的结果：";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}