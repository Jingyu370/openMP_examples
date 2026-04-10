#include <iostream>
#include <omp.h>
using namespace std;

int fib(int n) {
    int i, j;

    if (n < 2)
        return n;
    else {
        #pragma omp task shared(i)
        i = fib(n - 1);

        #pragma omp task shared(j)
        j = fib(n - 2);

        #pragma omp taskwait
        return i + j;
    }
}

int main() {
    const int num_threads = 4;
    omp_set_num_threads(num_threads);

    const int n = 10;

    cout << "=== OpenMP Parallel Fibonacci ===" << endl;
    cout << "Number of threads: " << num_threads << endl;
    cout << "Calculating fib(" << n << ")..." << endl;

    int result;
    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    cout << "fib(" << n << ") = " << result << endl;

    return 0;
}