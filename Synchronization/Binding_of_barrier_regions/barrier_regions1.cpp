/*  关键点：barrier只同步【最近一层 parallel】*/
#include <iostream>
#include <omp.h>
using namespace std;


void work(int n) {
    // 空函数，只模拟执行
}

void sub3(int n) {
    printf("线程 %d → 进入 sub3，准备 barrier\n", omp_get_thread_num());
    
    work(n);
    #pragma omp barrier
    work(n);
    
    printf("线程 %d → 通过 barrier，离开 sub3\n", omp_get_thread_num());
}


void sub2(int k) {
    printf("\n===== sub2 开始，创建新并行组 =====\n");
    #pragma omp parallel shared(k)
    {
        sub3(k);
    }
}

void sub1(int n) {
    printf("\n===== sub1 开始（外层大并行）=====\n");
    int i;
    #pragma omp parallel private(i) shared(n)
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            sub2(i);
        }
    }
}

int main() {
    omp_set_dynamic(0);
    omp_set_num_threads(2);

    printf("======== 调用 sub1(2) ========\n");
    sub1(2);

    printf("\n======== 调用 sub2(2) ========\n");
    sub2(2);

    printf("\n======== 调用 sub3(2) ========\n");
    sub3(2);

    return 0;
}