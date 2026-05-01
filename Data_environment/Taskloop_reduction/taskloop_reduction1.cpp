#include <iostream>
#include <omp.h>
using namespace std;

int array_sum(int n, int *v) {
    int res = 0;

    #pragma omp taskloop reduction(+:res)
    for (int i = 0; i < n; ++i)
        res += v[i];

    return res;
}

int main() {
    int n = 10;
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    #pragma omp parallel
    #pragma omp single
    {
        int res = array_sum(n, v);
        cout << "The result is " << res << endl;
    }
    // OUTPUT: The result is 55

    return 0;
}