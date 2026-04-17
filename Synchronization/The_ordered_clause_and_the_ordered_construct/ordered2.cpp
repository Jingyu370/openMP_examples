#include <cstdio>
#include <omp.h>

void work(int i) {}

void ordered_wrong(int n) {
    int i;
    #pragma omp parallel for ordered
    for (i = 0; i < n; i++) {
        // 错误：单次迭代执行了两个 ordered 区域
        #pragma omp ordered
        work(i);

        #pragma omp ordered
        work(i + 1);
    }
}

int main() {
    ordered_wrong(20);
    return 0;
}