#include <omp.h>
#include <iostream>
using namespace std;

#define N 100

int main(void){
    float a[N], b[N / 2];
    int i, j;

    for(int i = 0; i < N; i++){
        a[i] = i + 1;
    }

    j = 0;
    #pragma omp parallel
    #pragma omp for linear(j:1)
    for(i = 0;i < N; i += 2){
        b[j] = a[i] * 2.0f;
        j++;
    }

    printf("%d %f %f\n", j, b[0], b[j - 1]);
    
    return 0;
}