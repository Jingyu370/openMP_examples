#include <omp.h>
#include <iostream>
using namespace std;

void work(){

}

void foo(){
    #pragma omp parallel num_threads(16) proc_bind(close)
    {
        work();
    }
    return 0;
}