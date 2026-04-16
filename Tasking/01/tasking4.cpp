#include <iostream>
#include <omp.h>  // OpenMP 头文件

int main() {
    omp_lock_t lock;

    omp_init_lock(&lock);

    #pragma omp parallel
    {
        int i;

        #pragma omp for
        for (i = 0; i < 10; i++) {

            #pragma omp task
            {
                omp_set_lock(&lock);

                #pragma omp task
                {
                    printf("子任务执行\n");
                }

                omp_unset_lock(&lock);
            }
        }
    }

    // 销毁锁
    omp_destroy_lock(&lock);

    return 0;
}