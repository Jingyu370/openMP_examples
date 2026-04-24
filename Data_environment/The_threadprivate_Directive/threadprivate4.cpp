#include <iostream>
#include <omp.h>
using namespace std;

struct T {
    int t;
    
    T() : t(-1) {
        cout << "  调用默认构造 T()" << endl;
    }
    
    T(int v) : t(v) {
        cout << "  调用带参构造 T(" << v << ")" << endl;
    }
    
    T(const T& other) : t(other.t) {
        cout << "  调用拷贝构造 T(t=" << other.t << ")" << endl;
    }
    
    ~T() {}
};

T f() {
    cout << "  f() 被调用，返回 T(99)" << endl;
    return T(99);
}

static T t1;
#pragma omp threadprivate(t1)

static T t2(23);
#pragma omp threadprivate(t2)

static T t3 = f();
#pragma omp threadprivate(t3)

int main() {
    cout << "=== 全局初始化（主线程） ===" << endl;
    cout << "t1.t = " << t1.t << endl;
    cout << "t2.t = " << t2.t << endl;
    cout << "t3.t = " << t3.t << endl;
    cout << endl;

    cout << "=== 第 1 次并行区域 ===" << endl;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp critical
        {
            cout << "线程 " << omp_get_thread_num() << " 首次访问："
                 << " t1.t=" << t1.t
                 << " t2.t=" << t2.t
                 << " t3.t=" << t3.t << endl;
        }
    }
    cout << endl;

    cout << "=== 第 2 次并行区域（值保留） ===" << endl;
    #pragma omp parallel num_threads(2)
    {
        // 修改线程私有的值
        t1.t += 100;
        t2.t += 100;
        t3.t += 100;

        #pragma omp critical
        {
            cout << "线程 " << omp_get_thread_num() << " 修改后："
                 << " t1.t=" << t1.t
                 << " t2.t=" << t2.t
                 << " t3.t=" << t3.t << endl;
        }
    }
    cout << endl;

    cout << "=== 第 3 次并行区域（验证持久性） ===" << endl;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp critical
        {
            cout << "线程 " << omp_get_thread_num() << " 保留的值："
                 << " t1.t=" << t1.t
                 << " t2.t=" << t2.t
                 << " t3.t=" << t3.t << endl;
        }
    }

    return 0;
}