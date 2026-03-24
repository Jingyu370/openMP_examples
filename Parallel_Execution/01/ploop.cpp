#include <iostream>
#include <omp.h>
 
void simple(int n, double *a, double *b) {
    int i;

    // OpenMP 并行循环
    #pragma omp parallel for
    for (i = 1; i < n; i++) {
        b[i] = (a[i] + a[i-1]) / 2.0;
    }
}

int main() {
    int n = 20;
    double *a, *b;

    // 分配内存
    a = (double*)malloc(n * sizeof(double));
    b = (double*)malloc(n * sizeof(double));

    // 初始化数组 a：1, 2, 3, 4, ..., 20
    for (int i = 0; i < n; i++) {
        a[i] = (double)(i + 1);
    }

    // 调用并行函数
    simple(n, a, b);

    // 输出结果
    printf("数组 a:\n");
    for (int i = 0; i < n; i++) {
        printf("%.1f ", a[i]);
    }
    printf("\n\n数组 b (相邻平均):\n");
    for (int i = 1; i < n; i++) {
        printf("%.1f ", b[i]);
    }
    printf("\n");

    // 查看使用了多少线程
    printf("\nOpenMP 最大线程数 = %d\n", omp_get_max_threads());

    // 释放内存
    free(a);
    free(b);

    return 0;
}