#include <iostream>
#include <omp.h>
using namespace std;

int global_a = 0;

void g(int k) {
    global_a = k;
}

void f(int n) {
    int a = 0;

    #pragma omp parallel for private(a)
    for (int i = 1; i < n; i++) {
        a = i;
        g(a * 2);
    }
}

int main() {
    f(5);

    cout << "global_a = " << global_a << endl;
    // global_a 的值取决于哪个线程最后执行 g()，结果不确定

    return 0;
}