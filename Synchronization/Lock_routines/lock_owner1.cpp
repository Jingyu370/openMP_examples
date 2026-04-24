#include <omp.h>

int main()
{
    int x;
    omp_lock_t lck;

    omp_init_lock(&lck);
    omp_set_lock(&lck);
    x = 0;

    #pragma omp parallel shared(x)
    {
        #pragma omp master
        {
            omp_unset_lock(&lck);
            x = x + 1;
            omp_destroy_lock(&lck);
        }
    }

    return 0;
}