#include <iostream>
#include <omp.h>

int main() {
    int x = 0, y = 0;

    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) {
            x = 10;

            #pragma omp critical
            {
                y = 1;
            }
        } else {
            int tmp = 0;
            while (tmp == 0) {
                #pragma omp critical
                {
                    tmp = y;
                }
            }
            std::cout << "x = " << x << std::endl;
        }
    }
    return 0;
}