#include <omp.h>
#include <iostream>
using namespace std;

void work(){

}

int main(){ 
    #pragma omp parallel proc_bind(spread) num_threads(4)
    {
        work();
    }
    return 0;
}