#include <iostream>
#include <omp.h>
using namespace std;

int f(int res){
    return res * 2;
}

int g(int res){
    return res * 3;
}

int main(){
    int sum1 = 0, sum2 = 0;
    const int n = 100;

    #pragma omp target teams distribute reduction(+:sum1)
    for(int i = 0; i < n; i++){
        sum1 += f(i);
    }

    #pragma omp target teams distribute reduction(+:sum2)
    for(int i= 0;i < n; i++){
        sum2 += g(i) * sum1;
    }

    cout << "sum1 = " << sum1 << ",sum2 = " << sum2 <<endl;

    return 0;
}