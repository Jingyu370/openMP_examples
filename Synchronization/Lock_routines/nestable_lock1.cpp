#include <iostream>
#include <omp.h>

struct Pair {
    int a, b;
    omp_nest_lock_t lck;
};

void incr_a(Pair *p, int val)
{
    p->a += val;
}

void incr_b(Pair *p, int val)
{
    omp_set_nest_lock(&p->lck);
    p->b += val;
    omp_unset_nest_lock(&p->lck);
}

void incr_pair(Pair *p, int a, int b)
{
    omp_set_nest_lock(&p->lck);
    incr_a(p, a);
    incr_b(p, b);
    omp_unset_nest_lock(&p->lck);
}

int main()
{
    Pair p;
    p.a = 0;
    p.b = 0;
    omp_init_nest_lock(&p.lck);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            incr_pair(&p, 10, 20);
            std::cout << "section1: incr_pair(10, 20)" << std::endl;
        }

        #pragma omp section
        {
            incr_b(&p, 5);
            std::cout << "section2: incr_b(5)" << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "p.a = " << p.a << "（期望 10）" << std::endl;
    std::cout << "p.b = " << p.b << "（期望 25 = 20 + 5）" << std::endl;

    omp_destroy_nest_lock(&p.lck);
    return 0;
}
