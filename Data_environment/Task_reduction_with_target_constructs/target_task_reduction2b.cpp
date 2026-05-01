#include <iostream>
#include <omp.h>
using namespace std;

void device_compute(int *sum);
void host_compute(int *sum);

#pragma omp declare target to(device_compute)

int main() {
    int sum = 0;

    #pragma omp parallel master reduction(task, +:sum)
    {
        #pragma omp target in_reduction(+:sum) nowait
        device_compute(&sum);

        host_compute(&sum);
    }

    cout << "sum = " << sum << endl;
    // OUTPUT: sum = 2

    return 0;
}

void device_compute(int *sum) { *sum = 1; }
void host_compute(int *sum) { *sum = 1; }