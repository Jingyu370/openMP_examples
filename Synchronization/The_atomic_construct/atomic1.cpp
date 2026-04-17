/*1. example1
使用 atomic 构造避免竞态条件（多线程同时更新 x 的同一个元素）。
优势：可以并行更新 x 的不同元素。如果用 critical，所有更新都会串行执行。
注意：atomic 只保护紧跟它的那一条语句，所以 y[i] 的更新不是原子操作。
2. example2
展示 atomic 的 read 和 write 子句：
atomic read：保证变量被完整读取，读取过程中不会被其他线程修改。
atomic write：保证变量被完整写入，写入过程中其他线程看不到部分更新。
3. example3
展示 atomic 的 capture 子句：
原子地 “读取旧值 + 更新变量”，可以用硬件的 fetch-and-add 指令实现。
示例用 capture + read 实现了一个自旋锁（ticket 锁）。
*/

#include <iostream>
#include <omp.h>
using namespace std;

// 辅助工作函数
int work1(int i) { return i; }
int work2(int i) { return i * 2; }
void work() { }

// ------------------------------
// 示例 1：atomic 默认（update）
// ------------------------------
void example1() {
    cout << "===== 示例 1：atomic update =====" << endl;

    int x[10] = {0};
    int index[10] = {0,1,2,3,0,1,2,3,0,1};
    int y[10] = {0};

    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        // 原子更新：x 不会出错
        #pragma omp atomic
        x[index[i]] += work1(i);

        // 无保护：y 可能出错
        y[i] += work2(i);
    }

    cout << "x[0] = " << x[0] << endl;
    cout << "y[0] = " << y[0] << endl << endl;
}

// ------------------------------
// 示例 2：atomic read / write
// ------------------------------
void example2() {
    cout << "===== 示例 2：atomic read / write =====" << endl;

    int p = 100;
    int value;

    // 原子读
    #pragma omp atomic read
    value = p;

    cout << "原子读取 p = " << value << endl;

    // 原子写
    #pragma omp atomic write
    p = 999;

    cout << "原子写入后 p = " << p << endl << endl;
}

// ------------------------------
// 示例 3：atomic capture
// ------------------------------
struct lock_t {
    int ticketnumber;
    int turn;
};

void example3() {
    cout << "===== 示例 3：atomic capture =====" << endl;

    lock_t lock = {0, 0};

    #pragma omp parallel num_threads(4)
    {
        int myturn;

        // 原子捕获：读旧值 + 自增
        #pragma omp atomic capture
        { 
            myturn = lock.ticketnumber; 
            lock.ticketnumber++; 
        }

        // 自旋等待
        while (lock.turn != myturn) {}

        // 临界区工作
        work();
        cout << "线程 " << omp_get_thread_num() << " 工作中" << endl;

        // 释放锁
        #pragma omp atomic capture
        { 
            myturn = lock.turn; 
            lock.turn++; 
        }
    }
    cout << endl;
}

int main() {
    example1();
    example2();
    example3();
    return 0;
}