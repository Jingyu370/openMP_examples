#include <iostream>
#include <omp.h>

void work() {
    int thread_id = omp_get_thread_num();

    printf("线程 %d 正在执行任务\n", thread_id);
}

int main() {
    std::cout << "=== 开始并行区域（master策略，4线程）===" << std::endl;

    #pragma omp parallel proc_bind(master) num_threads(4)
    {
        work();
    }

    std::cout << "=== 并行区域结束 ===" << std::endl;
    return 0;
}