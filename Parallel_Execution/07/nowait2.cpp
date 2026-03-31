#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

void test(int n, float* a, float* b, float* c, float* z, float* y)
{
    int i;

    #pragma omp parallel
    {
        #pragma omp for schedule(static) nowait
        for (i = 0; i < n; i++) {
            c[i] = (a[i] + b[i]) / 2.0f;
            printf("线程 %d | 循环1 → c[%d] = %.2f\n", omp_get_thread_num(), i, c[i]);
        }

        #pragma omp for schedule(static) nowait
        for (i = 0; i < n; i++) {
            z[i] = sqrtf(c[i]);
            printf("线程 %d | 循环2 → z[%d] = %.2f\n", omp_get_thread_num(), i, z[i]);
        }

        #pragma omp for schedule(static) nowait
        for (i = 1; i <= n; i++) {
            y[i] = z[i-1] + a[i];
            printf("线程 %d | 循环3 → y[%d] = %.2f\n", omp_get_thread_num(), i, y[i]);
        }
    }
}

int main()
{
    const int n = 6;

    float a[n+1] = {1,2,3,4,5,6,7};
    float b[n]   = {9,8,7,6,5,4};
    float c[n]   = {0};
    float z[n]   = {0};
    float y[n+1] = {0};

    cout << "\n===== 开始并行计算 =====" << endl;
    test(n, a, b, c, z, y);

    cout << "\n===== 最终结果 =====" << endl;
    for(int i=0; i<n; i++) cout << "c["<<i<<"] = " << c[i] << endl;
    for(int i=0; i<n; i++) cout << "z["<<i<<"] = " << z[i] << endl;
    for(int i=1; i<=n; i++) cout << "y["<<i<<"] = " << y[i] << endl;

    return 0;
}