#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

float* work;
int arr_size; 
float tol;

#pragma omp threadprivate(work, arr_size, tol)

void build() {
    work = (float*)malloc(sizeof(float) * arr_size);
    for (int i = 0; i < arr_size; ++i)
        work[i] = tol;
}

void copyin_example(float t, int n) {
    tol = t;
    arr_size = n;

    #pragma omp parallel copyin(tol, arr_size)
    {
        build();
        #pragma omp critical
        cout << "线程 " << omp_get_thread_num()
             << " | tol = " << tol
             << " | arr_size = " << arr_size
             << " | work[0] = " << work[0]
             << " | work 地址 = " << work << endl;

    }
}

int main() {
    copyin_example(3.14f, 5);
    return 0;
}