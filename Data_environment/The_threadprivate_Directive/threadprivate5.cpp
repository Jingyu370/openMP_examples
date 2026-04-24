#include <iostream>
#include <omp.h>
using namespace std;

class T {
public:
    static int i;
#pragma omp threadprivate(i)
};

int T::i = 0;

int main() {
    cout << "=== 初始值 ===" << endl;
    cout << "T::i = " << T::i << endl;
    cout << endl;

    cout << "=== 第 1 次并行：每个线程独立累加 ===" << endl;
    #pragma omp parallel num_threads(3)
    {
        T::i++;

        #pragma omp critical
        cout << "线程 " << omp_get_thread_num()
             << " | T::i = " << T::i << endl;
    }
    cout << endl;

    cout << "=== 第 2 次并行：值跨区域保留 ===" << endl;
    #pragma omp parallel num_threads(3)
    {
        T::i++;    // 在上次的基础上继续累加

        #pragma omp critical
        cout << "线程 " << omp_get_thread_num()
             << " | T::i = " << T::i << endl;
    }
    cout << endl;

    cout << "=== 第 3 次并行：再累加一次 ===" << endl;
    #pragma omp parallel num_threads(3)
    {
        T::i++;

        #pragma omp critical
        cout << "线程 " << omp_get_thread_num()
             << " | T::i = " << T::i << endl;
    }

    return 0;
}