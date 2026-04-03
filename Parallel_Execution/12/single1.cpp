#include <iostream>
#include <omp.h>
using namespace std;

void work1() {}
void work2() {}

void single_example()
{
    #pragma omp parallel
    {
        #pragma omp single
        cout << "Beginning work1." << endl;

        work1();

        #pragma omp single
        cout << "Finishing work1" << endl;

        #pragma omp single nowait
        printf("Finished work1 and beginning work2.\n");

        work2();
    }
}

int main(){
    single_example();
    return 0;
}