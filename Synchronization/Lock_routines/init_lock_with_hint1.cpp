#include <omp.h>

omp_lock_t *new_locks() {
    omp_lock_t *lock = new omp_lock_t[1000];

    #pragma omp parallel for
    for (int i = 0; i < 1000; i++)
    {
        omp_init_lock_with_hint(&lock[i],
            static_cast<omp_lock_hint_t>(omp_lock_hint_contended |
                                          omp_lock_hint_speculative));
    }

    return lock;
}