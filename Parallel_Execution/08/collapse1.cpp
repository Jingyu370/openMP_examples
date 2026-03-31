#include <iostream>
#include <omp.h>
using namespace std;

void bar(float *a, int i, int j, int k);

int kl, ku, ks, jl, ju, js, il, iu, is;

void sub(float *a){
    int i, j, k;

    #pragma omp parallel
    {
        #pragma omp for collapse(2) private(i, j, k)
        for(k = kl; k <= ku; k+=ks)
        for(j = jl; j <= ju; j+=js)
        for(i = il; i <= iu; i+=is)
            bar(a, i ,j , k);
    }
}

void bar(float *a, int i, int j, int k) {
}

int main(){
    kl = 0; ku = 2; ks = 1;
    jl = 0; ju = 2; js = 1;
    il = 0; iu = 2; is = 1;
    float a[100];
    sub(a);
    cout << "运行成功！" << endl;
    return 0;
}