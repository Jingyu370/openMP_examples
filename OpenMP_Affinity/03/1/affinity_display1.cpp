#include <stdio.h>
#include <omp.h>

int main(void){
    omp_display_affinity(NULL);

    #pragma omp parallel num_threads(omp_get_num_procs()) proc_bind(spread)
    {
        if(omp_get_thread_num() == 0){
            printf("1st Parallel Region -- Affinity Reported\n");
        }
    }

    #pragma omp parallel num_threads(omp_get_num_procs()) proc_bind(spread)
    {
        if(omp_get_thread_num() == 0){
            printf("Same Affinity as in Previous Parallel Region -- no Affinity Reported\n");
        }
    }

    #pragma omp parallel num_threads(omp_get_num_procs()/2) proc_bind(spread)
    {
        if(omp_get_thread_num() == 0){
            printf("Report Affinity for using 1/2 of max threads.\n");
        }
    }

    return 0;
}