#include <omp.h>
#include <iostream>

void work(int i) {
    std::cout << "Thread " << i << " executed work()" << std::endl;
}

void correct() {
    int i;

    #pragma omp parallel private(i)
    {
        i = omp_get_thread_num();
        work(i);
    }
}

int main() {

    omp_set_num_threads(4);
    correct();
    return 0;
}