#include <iostream>
#include <cmath>
#include <omp.h>

float foo(int i) {
    return std::sin(i * 0.1f) * 10.0f;
}

float bar(float a, float b) {
    return a + b * 0.5f;
}

float baz(float b) {
    return std::sqrt(std::abs(b));
}

void work(int N, float *A, float *B, float *C)
{
    #pragma omp parallel for ordered(1)
    for (int i = 1; i < N; i++)
    {
        A[i] = foo(i);

        #pragma omp ordered depend(sink: i-1)
        B[i] = bar(A[i], B[i-1]);
        #pragma omp ordered depend(source)

        C[i] = baz(B[i]);
    }
}

int main()
{
    const int N = 20;
    float A[N], B[N], C[N];

    // 初始化
    A[0] = 0.0f;
    B[0] = 1.0f;
    C[0] = 0.0f;

    work(N, A, B, C);

    // 输出结果
    std::cout << "  i     A[i]        B[i]        C[i]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << i << "   "
                  << A[i] << "   "
                  << B[i] << "   "
                  << C[i] << std::endl;
    }

    return 0;
}