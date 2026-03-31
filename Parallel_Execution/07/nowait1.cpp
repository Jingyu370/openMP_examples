#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

void nowait_example(int n, int m, float* a, float* b, float* y, float* z) {
    int i;
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 1; i < n; i++) {
            b[i] = (a[i] + a[i - 1]) / 2.0f;
            cout << "[线程 " << omp_get_thread_num() << "] 计算 b[" << i << "] = " << b[i] << endl;
        }

        #pragma omp for nowait
        for (i = 0; i < m; i++) {
            y[i] = sqrt(z[i]);
            cout << "[线程 " << omp_get_thread_num() << "] 计算 y[" << i << "] = sqrt(" << z[i] << ") = " << y[i] << endl;
        }
    }
}

int main() {
    const int n = 5;
    const int m = 4;

    float a[n] = {1.0f, 3.0f, 5.0f, 7.0f, 9.0f};
    float z[m] = {4.0f, 9.0f, 16.0f, 25.0f};

    float b[n] = {0.0f};
    float y[m] = {0.0f};

    cout << "===== 开始并行计算（C++ + OpenMP nowait）=====" << endl;
    nowait_example(n, m, a, b, y, z);

    cout << "\n===== 最终计算结果 =====" << endl;
    for (int i = 1; i < n; i++) {
        cout << "b[" << i << "] = " << b[i] << endl;
    }
    for (int i = 0; i < m; i++) {
        cout << "y[" << i << "] = " << y[i] << endl;
    }

    return 0;
}