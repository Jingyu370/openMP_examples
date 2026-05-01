#include <iostream>
#include <omp.h>
using namespace std;

int main(void){
    int a, i;

    #pragma omp parallel
    {
        #pragma omp master
        a = 0;

        #pragma omp for reduction(+:a)
        for(i = 0;i < 10; i++){
            a += i;
        }

        #pragma omp single
        cout << "Sum is " << a << "." <<endl;
    }

    return 0;
}