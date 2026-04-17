#include <cstdio>

void work(int i) {}

void ordered_good(int n) {
    int i;
    #pragma omp parallel for ordered
    for (i = 0; i < n; i++) {
        if (i <= 10) {
            #pragma omp ordered
            work(i);
        }

        if (i > 10) {
            #pragma omp ordered
            work(i + 1);
        }
    }
}

int main() {
    ordered_good(20);
    return 0;
}