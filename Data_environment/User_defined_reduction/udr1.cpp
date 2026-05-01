#include <iostream>
#include <climits>
#include <omp.h>
using namespace std;

struct point { int x; int y; };

void minproc(point *out, point *in) {
    if (in->x < out->x) out->x = in->x;
    if (in->y < out->y) out->y = in->y;
}

void maxproc(point *out, point *in) {
    if (in->x > out->x) out->x = in->x;
    if (in->y > out->y) out->y = in->y;
}

#pragma omp declare reduction(min : point : minproc(&omp_out, &omp_in)) \
    initializer(omp_priv = { INT_MAX, INT_MAX })

#pragma omp declare reduction(max : point : maxproc(&omp_out, &omp_in)) \
    initializer(omp_priv = { 0, 0 })

void find_enclosing_rectangle(int n, point points[]) {
    point minp = {INT_MAX, INT_MAX}, maxp = {0, 0};

    #pragma omp parallel for reduction(min:minp) reduction(max:maxp)
    for (int i = 0; i < n; i++) {
        minproc(&minp, &points[i]);
        maxproc(&maxp, &points[i]);
    }

    cout << "min = (" << minp.x << ", " << minp.y << ")" << endl;
    cout << "max = (" << maxp.x << ", " << maxp.y << ")" << endl;
}

int main() {
    point points[] = {{3,5}, {1,8}, {6,2}, {4,7}};
    find_enclosing_rectangle(4, points);
    // OUTPUT:
    // min = (1, 2)
    // max = (6, 8)
    return 0;
}