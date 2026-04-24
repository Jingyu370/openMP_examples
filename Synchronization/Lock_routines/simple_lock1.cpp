#include <iostream>
#include <omp.h>

int main()
{
    omp_lock_t lck;
    int sum = 0;
    int other_work = 0;

    omp_init_lock(&lck);

    #pragma omp parallel shared(sum, other_work)
    {
        int tid = omp_get_thread_num();

        omp_set_lock(&lck);
        sum += tid;
        std::cout << "线程 " << tid << " (set_lock)  sum=" << sum << std::endl;
        omp_unset_lock(&lck);

        while (!omp_test_lock(&lck))
        {
            other_work += 1;
        }
        sum += tid * 10;
        std::cout << "线程 " << tid << " (test_lock) sum=" << sum
                  << " 等待期间做了 " << other_work << " 次额外计算" << std::endl;
        omp_unset_lock(&lck);
    }

    omp_destroy_lock(&lck);

    std::cout << std::endl;
    std::cout << "sum = " << sum << std::endl;
    std::cout << "other_work = " << other_work << "（等待期间完成的额外计算）" << std::endl;

    return 0;
}
