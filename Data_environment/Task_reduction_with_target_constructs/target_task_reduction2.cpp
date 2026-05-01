#include <iostream>
#include <omp.h>
using namespace std;

void device_compute(int *sum) { *sum = 1; }
void host_compute(int *sum) { *sum = 1; }

#pragma omp declare target to(device_compute)

int main() {
    int sum = 0;

    #pragma omp parallel sections reduction(task, +:sum)
    {
        #pragma omp section
        {
            #pragma omp target in_reduction(+:sum)
            device_compute(&sum);
        }
        #pragma omp section
        {
            host_compute(&sum);
        }
    }

    cout << "sum = " << sum << endl;
    // OUTPUT: sum = 2

    return 0;
}