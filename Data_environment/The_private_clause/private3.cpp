#include <iostream>
#include <cassert>
#include <omp.h>
using namespace std;

void priv_example3() {
    int i, a;

    #pragma omp parallel private(a)
    {
        a = 1;

        #pragma omp parallel for private(a)
        for (i = 0; i < 10; i++) {
            a = 2;
        }
        assert(a == 1);

        #pragma omp critical
        cout << "线程 " << omp_get_thread_num()
             << " | 外层 a = " << a << endl;
    }
}

int main() {
    priv_example3();
    return 0;
}