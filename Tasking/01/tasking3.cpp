#include <iostream>
#include <omp.h>
using namespace std;

int tp;
#pragma omp threadprivate(tp)
int var = 0;

void work() {
    #pragma omp parallel
    {
        #pragma omp critical
        cout << "Thread " << omp_get_thread_num() 
                  << " initial tp = " << tp << endl;

        #pragma omp task
        {
            int thread_id = omp_get_thread_num();
            tp++;
            #pragma omp critical
            cout << "Task A (Thread " << thread_id 
                      << "): tp++ → tp = " << tp << endl;

            #pragma omp taskyield
            for (volatile int i = 0; i < 10000; ++i);

            #pragma omp task
            {
                #pragma omp critical
                cout << "Task B (Thread " << thread_id 
                          << "): tp = " << tp << endl;
            }

            var = tp;
            #pragma omp critical
            cout << "Task A (Thread " << thread_id 
                      << "): var = tp → var = " << var << endl;
        }
    }
}

int main() {
    omp_set_num_threads(4);
    cout << "Initial global var = " << var 
              << ", global tp = " << tp << endl;

    work();

    cout << "Final global var = " << var << endl;
    return 0;
}