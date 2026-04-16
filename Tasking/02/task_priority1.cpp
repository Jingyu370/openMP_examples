/*OpenMP 中，priority 子句用于给任务设置优先级，优先级值越高，越容易被调度器优先执行。*/
#include <iostream>
#include <omp.h>

using namespace std;

void compute_array(float *node, int M, int task_id){
    printf("线程 %2d | 执行任务 i = %d\n", omp_get_thread_num(), task_id);
}

void compute_matrix(float *array, int N ,int M){
    int i;
    #pragma omp parallel private(i)
    #pragma omp single
    {
        printf("开始创建 %d 个任务，优先级 = i（数值越大优先级越高）\n\n", N);
        for (i = 0; i < N; i++){
            #pragma omp task priority(i)
            compute_array(&array[i * M], M, i);
        }
    }
}

int main(){
    omp_set_dynamic(0);
    omp_set_num_threads(4);

    const int N = 8;
    const int M = 10;
    float arr[N * M];

    compute_matrix(arr, N, M);
    return 0;
}