#include <iostream>
#include <omp.h>
using namespace std;

float x, y;
#pragma omp threadprivate(x, y)

void init(float a, float b) {
    #pragma omp single copyprivate(a, b, x, y)
    {
        a = 3.14f;
        b = 2.71f;
        x = 1.0f;
        y = 2.0f;
        cout << "[single] 线程 " << omp_get_thread_num()
             << " 设置: a=" << a << " b=" << b
             << " x=" << x << " y=" << y << endl;
    }
    #pragma omp critical
    cout << "  线程 " << omp_get_thread_num()
         << " | a=" << a << " b=" << b
         << " x=" << x << " y=" << y << endl;
}

int main() {
    #pragma omp parallel
    {
        init(0.0f, 0.0f);
    }
    return 0;
}