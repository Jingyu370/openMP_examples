#include <omp.h>
#include <stdio.h>

int main(){
    omp_set_dynamic(1);

    #pragma omp parallel num_threads(10)
    {
        #pragma omp single
        {
            int n = omp_get_num_threads();
            printf("totalsize: %d\n", n);
        }

        for(long i=0; i<100000000; i++);
    }

    return 0;
}