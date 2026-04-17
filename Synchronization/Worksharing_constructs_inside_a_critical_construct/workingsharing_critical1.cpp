/*核心：critical下不能直接仙桃single,for,section等语句，必须开一个parallel才合法*/

#include <iostream>
#include <omp.h>
using namespace std;

void critical_work() {
    int i = 1;
    cout << "初始 i = " << i << endl;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            #pragma omp critical(name)
            {
                cout << "\n线程 " << omp_get_thread_num() << " 进入临界区\n";

                // 嵌套并行：在临界区里新开一个并行区（合法！）
                #pragma omp parallel
                {
                    // single：只让一个线程执行一次
                    #pragma omp single
                    {
                        i++;
                        cout << "线程 " << omp_get_thread_num() 
                             << " 执行 i++ → i = " << i << endl;
                    }
                }

                cout << "线程 " << omp_get_thread_num() << " 离开临界区\n";
            }
        }
    }

    cout << "\n最终 i = " << i << endl;
}

int main() {
    omp_set_dynamic(0);
    omp_set_num_threads(4);

    critical_work();
    return 0;
}