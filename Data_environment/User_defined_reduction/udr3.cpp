#include <iostream>
#include <omp.h>
using namespace std;

#define N 100

struct mx_s {
    float value;
    int index;
};

void mx_combine(mx_s *out, mx_s *in) {
    if (out->value < in->value) {
        out->value = in->value;
        out->index = in->index;
    }
}

void mx_init(mx_s *priv, mx_s *orig) {
    priv->value = orig->value;
    priv->index = orig->index;
}

#pragma omp declare reduction(maxloc : mx_s : \
    mx_combine(&omp_out, &omp_in)) \
    initializer(mx_init(&omp_priv, &omp_orig))

int main() {
    mx_s mx;
    float val[N];
    int count = N;

    for (int i = 0; i < count; i++) {
        float d = (N * 0.8f - i);
        val[i] = N * N - d * d;
    }

    mx.value = val[0];
    mx.index = 0;

    #pragma omp parallel for reduction(maxloc: mx)
    for (int i = 1; i < count; i++) {
        if (mx.value < val[i]) {
            mx.value = val[i];
            mx.index = i;
        }
    }

    cout << "max value = " << mx.value << ", index = " << mx.index << endl;
    // OUTPUT: max value = 10000, index = 80

    return 0;
}