#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;

void reduction1(float *x, int *y, int n, float *a_out, int *b_out, int *c_out, float *d_out)
{
    int i, b, c;
    float a, d;

    a = 0.0;
    b = 0;
    c = y[0];
    d = x[0];

    #pragma omp parallel for private(i) shared(x, y, n) \
                         reduction(+:a) reduction(^:b) \
                         reduction(min:c) reduction(max:d)
    for (i=0; i<n; i++) {
        a += x[i];
        b ^= y[i];
        if (c > y[i]) c = y[i];
        d = fmaxf(d, x[i]);
    }

    *a_out = a;
    *b_out = b;
    *c_out = c;
    *d_out = d;
}

int main() {
    const int n = 5;
    float x[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    int y[] = {3, 1, 4, 1, 5};

    float a_sum, d_max;
    int b_xor, c_min;

    reduction1(x, y, n, &a_sum, &b_xor, &c_min, &d_max);

    cout << "数组 x: ";
    for (int i = 0; i < n; i++) cout << x[i] << " ";
    cout << "\n数组 y: ";
    for (int i = 0; i < n; i++) cout << y[i] << " ";
    cout << "\n\n归约结果：" << endl;
    cout << "x 的和 a = " << a_sum << endl;
    cout << "y 的异或结果 b = " << b_xor << endl;
    cout << "y 的最小值 c = " << c_min << endl;
    cout << "x 的最大值 d = " << d_max << endl;

    return 0;
}