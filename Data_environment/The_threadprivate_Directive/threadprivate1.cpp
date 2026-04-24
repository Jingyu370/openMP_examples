#include <omp.h>
#include <iostream>
using namespace std;

int counter = 0;
#pragma omp threadprivate(counter)

int increment_counter()
{
    counter++;
    return(counter);
}

int main(){
    for(int i = 0; i < 3; i++)
    {
        #pragma omp parallel
        {
            int val = increment_counter();
            #pragma omp critical
            cout << "循环 " << i 
                 << " | 线程 " << omp_get_thread_num() 
                 << " | counter = " << val << endl;
        }
    }
}