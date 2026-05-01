#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

float read_next() {
    float *tmp;
    float return_val;

    #pragma omp single copyprivate(tmp)
    {
        tmp = (float *)malloc(sizeof(float));
    }

    #pragma omp master
    {
        *tmp = 42.5f;  // 模拟 scanf("%f", tmp)
        cout << "[master] 写入 *tmp = " << *tmp << endl;
    }

    #pragma omp barrier
    return_val = *tmp;

    #pragma omp critical
    cout << "  线程 " << omp_get_thread_num()
         << " 读到 return_val = " << return_val
         << " | tmp地址 = " << tmp << endl;

    #pragma omp barrier

    #pragma omp single nowait
    {
        free(tmp);
    }

    return return_val;
}

int main() {
    #pragma omp parallel
    {
        float val = read_next();
        #pragma omp critical
        cout << "  线程 " << omp_get_thread_num()
             << " 返回值 = " << val << endl;
    }
    return 0;
}