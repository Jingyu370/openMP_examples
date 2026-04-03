#include <omp.h>
#include <cstdlib>
#include <iostream>

void do_by_16(float* x, int iam, int ipoints) {}

void dynthreads(float* x, int npoints) {
    int iam, ipoints;

    omp_set_dynamic(0);
    omp_set_num_threads(16);

    #pragma omp parallel shared(x, npoints) private(iam, ipoints)
    {
        if (omp_get_num_threads() != 16)
            abort();

        iam = omp_get_thread_num();
        ipoints = npoints / 16;
        do_by_16(x, iam, ipoints);
    }
}

int main() {
    const int n = 1600; 
    float* x = new float[n];

    std::cout << "启动16线程并行任务..." << std::endl;
    dynthreads(x, n);
    std::cout << "任务执行完成（线程数校验通过）" << std::endl;

    delete[] x;
    return 0;
}