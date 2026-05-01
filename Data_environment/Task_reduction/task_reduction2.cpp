#include <iostream>
#include <omp.h>

int main() {
    int N = 100, M = 10;
    int i, x;

    x = 0;
    #pragma omp parallel num_threads(M) reduction(task, +:x)
    {
        x++;
        #pragma omp single
        for (i = 0; i < N; ++i) {
            #pragma omp task in_reduction(+:x)
            x++;
        }
    }
    std::cout << "x = " << x << " (expected: M + N = " << M + N << ")\n";

    x = 0;
    #pragma omp parallel for num_threads(M) reduction(task, +:x)
    for (i = 0; i < N; ++i) {
        x++;
        if (i % 2 == 0) {
            #pragma omp task in_reduction(+:x)
            x--;
        }
    }
    std::cout << "x = " << x << " (expected: N - N/2 = " << N - N/2 << ")\n";

    return 0;
}