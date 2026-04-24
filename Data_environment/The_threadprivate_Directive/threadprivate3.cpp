#include <iostream>
#include <omp.h>
using namespace std;

class T {
public:
    int val;
    T(int v) : val(v) {}
    T(const T& t) : val(t.val) {}
};

void g(T a, T b) {
    a.val += b.val;
}

int x = 1;
T a(x);
const T b_aux(x);
T b(b_aux);
#pragma omp threadprivate(a, b)

void f(int n) {
    x++;

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int thread_id = omp_get_thread_num();

        #pragma omp critical
        {
            cout << "线程 " << thread_id
                 << " | 迭代 i=" << i
                 << " | a.val=" << a.val
                 << " | b.val=" << b.val
                 << " | a.val+b.val=" << a.val + b.val
                 << endl;
        }

        g(a, b);
    }
}

int main() {
    cout << "=== 初始状态 ===" << endl;
    cout << "x = " << x << endl;
    cout << "a.val = " << a.val << endl;
    cout << "b.val = " << b.val << endl;
    cout << endl;

    cout << "=== 进入 f(6) ===" << endl;
    f(6);

    return 0;
}