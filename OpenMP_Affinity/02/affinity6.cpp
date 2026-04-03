#include <iostream>
#include <omp.h>

// 分配并初始化 B 数组
double* alloc_init_B(double* A, int N) {
    double* B = new double[N];
    for (int i = 0; i < N; ++i) {
        B[i] = A[i] * 2.0;
    }
    return B;
}

// 在 B 数组上执行计算
void compute_on_B(double* B, int N) {
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        sum += B[i];
    }
    std::cout << "  任务[线程 " << omp_get_thread_num() 
              << "]: 计算总和 = " << sum << std::endl;
}

void task_affinity(double* A, int N) {
    double* B = nullptr;

    std::cout << "\n=== 开始任务亲和性演示 ===" << std::endl;

    // ---------------- 任务 1：分配 B ----------------
    #pragma omp task depend(out: B) shared(B) affinity(A[0:N])
    {
        std::cout << "任务1[线程 " << omp_get_thread_num() 
                  << "]: 分配并初始化 B" << std::endl;
        B = alloc_init_B(A, N);
    }

    // ---------------- 任务 2：使用 B ----------------
    #pragma omp task depend(in: B) shared(B) affinity(A[0:N])
    {
        std::cout << "任务2[线程 " << omp_get_thread_num() 
                  << "]: 开始计算 B" << std::endl;
        compute_on_B(B, N);
    }

    #pragma omp taskwait

    std::cout << "=== 所有任务完成 ===" << std::endl;

    delete[] B;
}

int main() {
    const int N = 10000;
    double* A = new double[N];

    for (int i = 0; i < N; ++i) {
        A[i] = static_cast<double>(i);
    }

    #pragma omp parallel num_threads(2)
    #pragma omp single
    {
        task_affinity(A, N);
    }

    delete[] A;
    return 0;
}