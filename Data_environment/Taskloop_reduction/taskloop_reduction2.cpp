#include <iostream>
#include <omp.h>
using namespace std;

int array_sum(int n, int *v) {
    int res = 0;

    #pragma omp taskgroup task_reduction(+:res)
    {
        if (n > 0) {
            #pragma omp task in_reduction(+:res)
            res = res + v[0];

            #pragma omp taskloop in_reduction(+:res) nogroup
            for (int i = 1; i < n; ++i)
                res += v[i];
        }
    }

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