#include <omp.h>
#include <iostream>

using namespace std;

void work(int a, int j, int i);

void sub()
{
    int j, k, a;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp for collapse(2) ordered private(j,k) schedule(static,3)
        for (k=1; k<=3; k++)
        for (j=1; j<=2; j++)
    {
        #pragma omp ordered
        printf("%d %d %d\n", omp_get_thread_num(), k, j);
        work(a,j,k);
    }
}
}