#include <iostream>
#include <omp.h>

int main(){
    omp_set_dynamic(0);
    #pragma omp parallel num_threads(10)
    {
        int total = omp_get_num_threads();
        #pragma omp single
        {
            printf("totalsize: %d\n", total);
        }
    }

    return 0;
}