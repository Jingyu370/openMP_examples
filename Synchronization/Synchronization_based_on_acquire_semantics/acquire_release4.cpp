#include <iostream>
#include <omp.h>

int main() {
    //错误代码：无法保证读到 x=10
    int x = 0, y = 0;

    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) {
            #pragma omp critical
            {
                x = 10;
            }

            #pragma omp atomic write
            y = 1;
        } else {
            int tmp = 0;
            while (tmp == 0) {
                #pragma omp atomic read acquire
                tmp = y;
            }

            #pragma omp critical
            {
                std::cout << "x = " << x << std::endl;  // 可能输出 0 或 10
            }
        }
    }
    return 0;
}