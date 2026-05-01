#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;

float condlastprivate(float *a, int n)
{
    float x = 0.0f;

    #pragma omp parallel for simd lastprivate(conditional: x)
    for (int k = 0; k < n; k++) {
        if (a[k] < 108.5 || a[k] > 208.5) {
            x = sinf(a[k]);
        }
    }

    return x;
}

int main() {
    float a[] = {100, 150, 180, 200, 220, 170, 190};
    int n = sizeof(a) / sizeof(a[0]);

    cout << "数组长度 n = " << n << endl;
    cout << "数组内容：";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    float result = condlastprivate(a, n);

    cout << "\n最终 x = sinf(220) = " << result << endl;

    return 0;
}