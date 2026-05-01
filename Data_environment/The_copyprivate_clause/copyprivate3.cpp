#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

omp_lock_t *new_lock() {
    omp_lock_t *lock_ptr;

    #pragma omp single copyprivate(lock_ptr)
    {
        lock_ptr = (omp_lock_t *)malloc(sizeof(omp_lock_t));
        omp_init_lock(lock_ptr);
        cout << "[single] 线程 " << omp_get_thread_num()
             << " 分配锁，地址 = " << lock_ptr << endl;
    }

    return lock_ptr;
}

int main() {
    omp_lock_t *my_lock = nullptr;

    #pragma omp parallel
    {
        my_lock = new_lock();

        #pragma omp critical
        {
            cout << "  线程 " << omp_get_thread_num()
                 << " | my_lock = " << my_lock << endl;
        }

        omp_set_lock(my_lock);
        cout << "  线程 " << omp_get_thread_num() << " 持有锁" << endl;
        omp_unset_lock(my_lock);
    }

    // 并行区外释放锁
    omp_destroy_lock(my_lock);
    free(my_lock);
    return 0;
}