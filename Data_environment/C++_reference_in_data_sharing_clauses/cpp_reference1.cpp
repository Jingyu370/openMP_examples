#include <iostream>
#include <omp.h>
using namespace std;

void task_body(int &x) {
    #pragma omp critical
    cout << "    [task] 线程 " << omp_get_thread_num()
         << " | x = " << x << " | &x = " << &x << endl;
}

void gen_task(int &x) {
    #pragma omp task
    task_body(x);
}

void test(int &y, int &z) {
    #pragma omp parallel private(y)
    {
        y = z + 2;
        #pragma omp critical
        cout << "线程 " << omp_get_thread_num()
             << " | y = " << y << " | &y = " << &y
             << " | z = " << z << " | &z = " << &z << endl;

        gen_task(y);
        gen_task(z);

        y++;
        gen_task(y);
    }
    #pragma omp taskwait
}

int main() {
    int a = 10, b = 100;
    test(a, b);
    return 0;
}