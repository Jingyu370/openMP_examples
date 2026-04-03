#include <iostream>
#include <vector>
#include <omp.h>

void iterator_example() {
    std::vector<int> vec(23);

    #pragma omp parallel for default(none) shared(vec)
    for (int i = 0; i < (int)vec.size(); ++i) {
        vec[i] = omp_get_thread_num();
    }

    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    iterator_example();
    return 0;
}