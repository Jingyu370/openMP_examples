#include <iostream>
#include <cmath>
#include <omp.h>

#define N 100

int main()
{
    float x[N], y[N];
    float a = 2.0f;

    for (int i = 0; i < N; ++i) {
        x[i] = static_cast<float>(i);
        y[i] = 0.0f;
    }

    #pragma omp parallel
    {
        #pragma omp loop
        for (int i = 0; i < N; ++i) {
            y[i] = a * x[i] + y[i];
        }
    }

    const float expected = static_cast<float>((N - 1) * 2.0);
    if (std::fabs(y[N-1] - expected) > 1e-6) {
        std::cout << "Error: 2*(N-1) != y[N-1] = " << y[N-1] << std::endl;
    } else {
        std::cout << "Success: y[N-1] = " << y[N-1] << std::endl;
    }

    return 0;
}