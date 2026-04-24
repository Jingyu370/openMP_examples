#include <iostream>
#include <cassert>
#include <omp.h>
using namespace std;

int main() {
    int i, j;
    int *ptr_i, *ptr_j;

    i = 1;
    j = 2;

    ptr_i = &i;
    ptr_j = &j;

    #pragma omp parallel private(i) firstprivate(j)
    {
        i = 3;
        j = j + 2;

        assert(*ptr_i == 1 && *ptr_j == 2);

        #pragma omp critical
        {
            cout << "线程 " << omp_get_thread_num()
                 << " | 私有 i = " << i
                 << " | 私有 j = " << j
                 << " | *ptr_i = " << *ptr_i
                 << " | *ptr_j = " << *ptr_j << endl;
        }
    }

    assert(i == 1 && j == 2);
    cout << "退出并行区域后：i = " << i << ", j = " << j << endl;

    return 0;
}