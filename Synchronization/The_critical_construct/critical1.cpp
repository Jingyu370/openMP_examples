#include <iostream>
#include <omp.h>
#include <unistd.h>
#include <cstdlib>

int queue_x[10];
int queue_y[10];
int head_x = 0;
int head_y = 0;

int dequeue(float *a) {
    if (a == (float*)queue_x) {
        if (head_x >= 10) return -1;
        return queue_x[head_x++];
    } else if (a == (float*)queue_y) {
        if (head_y >= 10) return -1;
        return queue_y[head_y++];
    }
    return -1;
}

void work(int i, float *a) {
    int tid = omp_get_thread_num();
    const char* name = (a == (float*)queue_x) ? "X队列" : "Y队列";
    printf("线程 %d：正在处理 %s 的任务 %d\n", tid, name, i);
    sleep(1);
}

void critical_example(float *x, float *y) {
    int ix_next, iy_next;

    #pragma omp parallel shared(x, y) private(ix_next, iy_next)
    {
        #pragma omp critical (xaxis)
        ix_next = dequeue(x);
        if (ix_next != -1) {
            work(ix_next, x);
        }

        #pragma omp critical (yaxis)
        iy_next = dequeue(y);
        if (iy_next != -1) {
            work(iy_next, y);
        }
    }
}

int main() {
    for (int i = 0; i < 10; i++) {
        queue_x[i] = i;
        queue_y[i] = i + 100;
    }
    head_x = 0;
    head_y = 0;

    printf("===== 版本1：基础命名critical（独立锁）=====\n");
    critical_example((float*)queue_x, (float*)queue_y);

    return 0;
}