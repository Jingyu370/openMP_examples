#include <iostream>
#include <omp.h>
using namespace std;

#define N 100

int main() {
    int a[N], b[N];
    int x = 0;

    for (int k = 0; k < N; k++)
        a[k] = k + 1;

    #pragma omp parallel for simd reduction(inscan, +: x)
    for (int k = 0; k < N; k++) {
        b[k] = x;
        #pragma omp scan exclusive(x)
        x += a[k];
    }

    cout << "x = " << x << ", b[0:3] = " << b[0] << " " << b[1] << " " << b[2] << endl;
    // OUTPUT: x = 5050, b[0:3] = 0 1 3

    return 0;
}