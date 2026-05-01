#include <iostream>
#include <memory>
#include <omp.h>

#define N 10

struct node_t {
    int val;
    node_t* next;

    node_t(int v) : val(v), next(nullptr) {}
};

int linked_list_sum(node_t* p)
{
    int res = 0;

    #pragma omp taskgroup task_reduction(+: res)
    {
        node_t* aux = p;
        while (aux != nullptr)
        {
            #pragma omp task in_reduction(+: res)
            res += aux->val;

            aux = aux->next;
        }
    }
    return res;
}

void free_linked_list(node_t* root)
{
    node_t* current = root;
    while (current != nullptr)
    {
        node_t* next = current->next;
        delete current;
        current = next;
    }
}

int main()
{
    node_t* root = new node_t(1);
    node_t* aux = root;

    for (int i = 2; i <= N; ++i)
    {
        aux->next = new node_t(i);
        aux = aux->next;
    }
    aux->next = nullptr;

    #pragma omp parallel
    #pragma omp single
    {
        int result = linked_list_sum(root);
        int analytic_sum = N * (N + 1) / 2;

        std::cout << "Calculated sum: " << result << std::endl;
        std::cout << "Analytic sum:   " << analytic_sum << std::endl;
    }

    free_linked_list(root);

    return 0;
}