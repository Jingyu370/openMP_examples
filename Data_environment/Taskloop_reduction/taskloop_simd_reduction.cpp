#include <iostream>
#include <omp.h>
using namespace std;

#define N 100

int main() {
    int a[N], asum = 0;
    for (int i = 0; i < N; i++) a[i] = i;

    // ===== taskloop reductions =====

    // 写法 A：独立归约
    asum = 0;
    #pragma omp parallel master
    #pragma omp taskloop reduction(+:asum)
    for (int i = 0; i < N; i++) { asum += a[i]; }

    // 写法 B：参与 parallel 归约
    asum = 0;
    #pragma omp parallel reduction(task, +:asum)
    {
        #pragma omp master
        #pragma omp task in_reduction(+:asum)
        for (int i = 0; i < N; i++) { asum += a[i]; }

        #pragma omp master taskloop in_reduction(+:asum)
        for (int i = 0; i < N; i++) { asum += a[i]; }
    }

    // ===== taskloop simd reductions =====

    // 写法 C：独立归约
    asum = 0;
    #pragma omp parallel master
    #pragma omp taskloop simd reduction(+:asum)
    for (int i = 0; i < N; i++) { asum += a[i]; }

    // 写法 D：参与 parallel 归约
    asum = 0;
    #pragma omp parallel reduction(task, +:asum)
    {
        #pragma omp master
        #pragma omp task in_reduction(+:asum)
        for (int i = 0; i < N; i++) { asum += a[i]; }

        #pragma omp master taskloop simd in_reduction(+:asum)
        for (int i = 0; i < N; i++) { asum += a[i]; }
    }

    cout << "asum = " << asum << endl;
    // OUTPUT: asum = 29700

    return 0;
}