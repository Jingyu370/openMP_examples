#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

float average(float a, float b, float c) {
    return (a + b + c) / 3.0f;
}

void master_example(vector<float>& x, vector<float>& xold, float tol) {
    int n = x.size();
    int c = 0;
    int toobig, i;
    float error, y;

    #pragma omp parallel
    {
        do {
            #pragma omp for private(i)
            for (i = 1; i < n - 1; ++i) {
                xold[i] = x[i];
            }

            #pragma omp single
            {
                toobig = 0;
            }

            #pragma omp for private(i, y, error) reduction(+:toobig)
            for (i = 1; i < n - 1; ++i) {
                y = x[i];
                x[i] = average(xold[i-1], x[i], xold[i+1]);
                error = fabs(y - x[i]);

                if (error > tol) {
                    toobig++;
                }
            }

            #pragma omp master
            {
                c++;
                cout << "iteration " << c << ", toobig = " << toobig << endl;
            }

        } while (toobig > 0);
    }
}

int main() {
    const int n = 20;          // 数组大小
    const float tol = 0.001f;   // 收敛精度

    vector<float> x(n, 0.0f);
    vector<float> xold(n, 0.0f);

    // 初始化：边界=0，内部=1
    for (int i = 1; i < n-1; ++i) {
        x[i] = 1.0f;
    }

    cout << "开始迭代求解..." << endl;
    master_example(x, xold, tol);

    cout << "\n最终结果：" << endl;
    for (float val : x) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}