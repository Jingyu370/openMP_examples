#include <cstdio>
#include <cstdlib>
#include <omp.h>

void socket_work(int socket_num, int n_thrds);

int main(void)
{
    int n_sockets, socket_num, n_thrds_on_socket;

    omp_set_nested(1);
    omp_set_max_active_levels(2);

    n_sockets = omp_get_num_places();
    n_thrds_on_socket = omp_get_place_num_procs(0);

    // ===================== 环境变量参考 =====================
    // OMP_NUM_THREADS=2,4
    // OMP_PLACES="{0,2,4,6},{1,3,5,7}"
    // OMP_AFFINITY_FORMAT="nest_level= %L, parent_thrd_num= %a, thrd_num= %n, thrd_affinity= %A"
    // ========================================================

    #pragma omp parallel num_threads(n_sockets) private(socket_num)
    {
        socket_num = omp_get_place_num();

        if (socket_num == 0) {
            printf(" LEVEL 1 AFFINITIES 1 thread/socket, %d sockets:\n\n", n_sockets);
        }

        omp_display_affinity(NULL);

        socket_work(socket_num, n_thrds_on_socket);
    }

    return 0;
}

void socket_work(int socket_num, int n_thrds)
{
    #pragma omp parallel num_threads(n_thrds)
    {
        if (omp_get_thread_num() == 0) {
            printf(" LEVEL 2 AFFINITIES, %d threads on socket %d\n", n_thrds, socket_num);
        }

        omp_display_affinity(NULL);

        // ===================== workplace =====================
        // 
        // ==============================================================
    }
}