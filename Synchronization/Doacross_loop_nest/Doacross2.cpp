#include <iostream>
#include <cmath>
#include <omp.h>

float foo(int i, int j) {
    return std::sin(i * 0.1f) * std::cos(j * 0.1f) * 10.0f;
}

float bar(float a, float b, float c) {
    return a + b * 0.3f + c * 0.3f;
}

float baz(float b) {
    return std::sqrt(std::abs(b));
}

void work(int N, int M, float **A, float **B, float **C)
{
    #pragma omp parallel for ordered(2) collapse(2)
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < M; j++)
        {
            A[i][j] = foo(i, j);

            #pragma omp ordered depend(sink: i-1,j) depend(sink: i,j-1)
            B[i][j] = bar(A[i][j], B[i-1][j], B[i][j-1]);
            #pragma omp ordered depend(source)

            C[i][j] = baz(B[i][j]);
        }
    }
}

int main()
{
    const int N = 6, M = 6;

    float **A = new float*[N];
    float **B = new float*[N];
    float **C = new float*[N];
    for (int i = 0; i < N; i++) {
        A[i] = new float[M]();
        B[i] = new float[M]();
        C[i] = new float[M]();
    }

    for (int i = 0; i < N; i++) B[i][0] = 1.0f;
    for (int j = 0; j < M; j++) B[0][j] = 1.0f;

    work(N, M, A, B, C);

    std::cout << "B[i][j] 结果：" << std::endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            std::cout << B[i][j] << "\t";
        std::cout << std::endl;
    }

    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}