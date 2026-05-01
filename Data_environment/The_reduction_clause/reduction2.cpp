#include <iostream>
#include <math.h>
#include <limits.h>
#include <omp.h>
using namespace std;

void reduction2(float *x, int *y, int n,
                float *out_a, int *out_b, int *out_c, float *out_d)
{
    int i, b, b_p, c, c_p;
    float a, a_p, d, d_p;

    a = 0.0f;
    b = 0;
    c = y[0];
    d = x[0];

    #pragma omp parallel shared(a, b, c, d, x, y, n) private(a_p, b_p, c_p, d_p)
    {
        a_p = 0.0f;
        b_p = 0;
        c_p = INT_MAX;
        d_p = -HUGE_VALF;

        #pragma omp for private(i)
        for (i = 0; i < n; i++) {
            a_p += x[i];
            b_p ^= y[i];

            if (c_p > y[i])
                c_p = y[i];

            d_p = fmaxf(d_p, x[i]);
        }

        #pragma omp critical
        {
            a += a_p;
            b ^= b_p;

            if (c > c_p)
                c = c_p;

            d = fmaxf(d, d_p);
        }
    }

    *out_a = a;
    *out_b = b;
    *out_c = c;
    *out_d = d;
}

int main() {
    const int n = 5;
    float x[] = {1.5f, 2.5f, 3.5f, 4.5f, 5.5f};
    int y[]   = {1, 2, 3, 4, 5};

    float sum_a, max_d;
    int xor_b, min_c;

    reduction2(x, y, n, &sum_a, &xor_b, &min_c, &max_d);

    cout << "数组 x：";
    for (int i=0; i<n; i++) cout << x[i] << " ";
    cout << endl;

    cout << "数组 y：";
    for (int i=0; i<n; i++) cout << y[i] << " ";
    cout << endl;

    cout << "\n===== 归约结果 =====" << endl;
    cout << "求和 a = " << sum_a << endl;
    cout << "异或 b = " << xor_b << endl;
    cout << "最小值 c = " << min_c << endl;
    cout << "最大值 d = " << max_d << endl;

    return 0;
}