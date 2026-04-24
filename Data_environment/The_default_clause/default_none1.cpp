#include <iostream>
#include <omp.h>
using namespace std;

int x, y, z[1000];
#pragma omp threadprivate(x)

void default_none(int a) {
    const int c = 1;
    int i = 0;

    #pragma omp parallel default(none) private(a) shared(z, c)
    {
        int j = omp_get_num_threads();

        a = z[j];

        x = c;

        // z[i] = y;
        // i 和 y 未声明数据共享属性

        // #pragma omp for firstprivate(y)
        // y 在 default(none) 下已不可引用，不能在子句中补救

        for (int i = 0; i < 10; i++) {
            z[i] = i;
        }

        // z[i] = y;
        // 离开 for 后 i 不再是循环变量，i 和 y 都不可引用
    }
}

int main() {
    for (int i = 0; i < 1000; i++) {
        z[i] = i;
    }

    default_none(0);

    return 0;
}