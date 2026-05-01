#include <iostream>
#include <omp.h>
using namespace std;

#define N 100

void init(int n, float b[][N]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] = i + j;
}

int main() {
    int i, j;
    float a[N], b[N][N];

    init(N, b);

    for (i = 0; i < N; i++) a[i] = 0.0f;

    #pragma omp parallel for reduction(+:a[0:N]) private(j)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[j] += b[i][j];
        }
    }

    cout << "a[0] = " << a[0] << endl;
    cout << "a[N-1] = " << a[N-1] << endl;

    // 验证：a[j] = sum(b[i][j]) for i=0..N-1
    // b[i][j] = i+j, 所以 a[j] = sum(i+j, i=0..N-1) = N*(N-1)/2 + N*j
    // a[0] = 4950, a[99] = 14850
    cout << "验证 a[0] = " << N * (N - 1) / 2 << endl;
    cout << "验证 a[N-1] = " << N * (N - 1) / 2 + N * (N - 1) << endl;

    return 0;
}