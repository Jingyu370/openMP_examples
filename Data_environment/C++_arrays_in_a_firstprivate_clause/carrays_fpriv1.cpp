#include <iostream>
#include <cassert>
#include <omp.h>
using namespace std;

int A[2][2] = {1, 2, 3, 4};

void f(int n, int B[][2], int C[]) {
    int D[2][2] = {1, 2, 3, 4};
    int* E_data = new int[n * n];
    int (*E)[2] = (int (*)[2])E_data;
    E[1][1] = 4;

    #pragma omp parallel firstprivate(B, C, D)
    {
        assert(&B[1][1] == &A[1][1]);
        assert(&C[3] == &A[1][1]);

        assert(D[1][1] == 4);

        D[0][0] = 99;

        #pragma omp critical
        {
            cout << "线程 " << omp_get_thread_num() << endl;
            cout << "  B[1][1] = " << B[1][1] << " (指向原始 A)" << endl;
            cout << "  C[3]   = " << C[3] << " (指向原始 A)" << endl;
            cout << "  D[1][1] = " << D[1][1] << " (独立副本)" << endl;
            cout << "  D[0][0] = " << D[0][0] << " (修改了副本)" << endl;
        }
    }

    assert(D[0][0] == 1);
    assert(D[1][1] == 4);
    cout << "\n退出并行区域后 D[0][0] = " << D[0][0] << " (原始值不变)" << endl;

    delete[] E_data;
}

int main() {
    f(2, A, A[0]);
    return 0;
}