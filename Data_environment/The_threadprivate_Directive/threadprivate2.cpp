#include <omp.h>
#include <iostream>
using namespace std;

int increment_counter_2()
{
    static int counter = 0; //效力只在函数内，更满足封装性
    #pragma omp threadprivate(counter)
    counter++;
    return (counter);
}

int main(){
        for(int i = 0; i < 3; i++)
    {
        #pragma omp parallel
        {
            int val = increment_counter_2();
            #pragma omp critical
            cout << "循环 " << i 
                 << " | 线程 " << omp_get_thread_num() 
                 << " | counter = " << val << endl;
        }
    }
}