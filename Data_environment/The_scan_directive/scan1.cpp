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
        x += a[k];
        #pragma omp scan inclusive(x)
        b[k] = x;
    }

    cout << "x = " << x << ", b[0:3] = " << b[0] << " " << b[1] << " " << b[2] << endl;
    // OUTPUT: x = 5050, b[0:3] = 1 3 6

    return 0;
}