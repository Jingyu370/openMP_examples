#include <iostream>
#include <omp.h>

#define N 100

void driver(bool update, float a[], float b[], int n, omp_depend_t* obj);
void update_copy(bool update, float a[], float b[], int n);
void checkpoint(float a[], int n);
void init(float a[], int n);

int main() {
    float a[N], b[N];
    omp_depend_t obj;

    init(a, N);

    #pragma omp depobj(obj) depend(inout: a)

    driver(true, a, b, N, &obj);

    #pragma omp depobj(obj) update(in)

    driver(false, a, b, N, &obj);

    #pragma omp depobj(obj) destroy

    return 0;
}

void driver(bool update, float a[], float b[], int n, omp_depend_t* obj) {
    #pragma omp parallel num_threads(2)
    #pragma omp single
    {
        // 任务1：使用依赖对象
        #pragma omp task depend(depobj: *obj)
        update_copy(update, a, b, n);

        // 任务2：直接声明 in 依赖
        #pragma omp task depend(in: a[:n])
        checkpoint(a, n);
    }
}

void init(float a[], int n) {
    for (int i = 0; i < n; ++i) {
        a[i] = static_cast<float>(i);
    }
}

void update_copy(bool update, float a[], float b[], int n) {
    if (update) {
        for (int i = 0; i < n; ++i) {
            a[i] += 1.0f;
        }
    }
    for (int i = 0; i < n; ++i) {
        b[i] = a[i];
    }
}

void checkpoint(float a[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}