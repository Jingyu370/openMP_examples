#include <iostream>
#include <omp.h>
using namespace std;

class V {
    float *p;
    int n;

public:
    V() : n(0), p(new float[1]) {}
    V(int _n) : n(_n) { p = new float[n](); } 
    V(const V& m) : n(m.n) {
        p = new float[n];
        for (int i = 0; i < n; i++) p[i] = m.p[i];
    }
    ~V() { delete[] p; }

    V& operator=(const V& rhs) {
        if (this != &rhs) {
            delete[] p;
            n = rhs.n;
            p = new float[n];
            for (int i = 0; i < n; i++) p[i] = rhs.p[i];
        }
        return *this;
    }

    V& operator+=(const V& rhs) {
        if (n == 0 && rhs.n > 0) {
            n = rhs.n;
            delete[] p;
            p = new float[n]();
        }
        for (int i = 0; i < n && i < rhs.n; i++)
            p[i] += rhs.p[i];
        return *this;
    }

    #pragma omp declare reduction(+ : V : omp_out += omp_in) \
            initializer(omp_priv(omp_orig))

    void set(int i, float val) { p[i] = val; }
    float get(int i) const { return p[i]; }
    int size() const { return n; }
};

int main() {
    int n = 10;
    V total(n);
    V a(n), b(n), c(n);

    for (int i = 0; i < n; i++) {
        a.set(i, i * 1.0f);
        b.set(i, i * 2.0f);
        c.set(i, i * 3.0f);
    }

    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < n; i++) {
        V tmp(n);
        for (int j = 0; j < n; j++)
            tmp.set(j, a.get(i) + b.get(i) + c.get(i));
        total += tmp;
    }

    cout << "total = {";
    for (int i = 0; i < n; i++) {
        cout << total.get(i);
        if (i < n - 1) cout << ", ";
    }
    cout << "}" << endl;

    cout << "验证：total[0] = " << 6 * 45 << ", total[9] = " << 6 * 45 << endl;

    return 0;
}