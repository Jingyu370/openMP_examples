// affinity_display.3_fixed.cpp (OpenMP 5.0 兼容 C++)
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <omp.h>

#define FORMAT_STORE  80
#define BUFFER_STORE  80

int main(void)
{
    int i, n, thrd_num, max_req_store;
    size_t nchars;

    char default_format[FORMAT_STORE];
    const char my_format[] = "host=%20H thrd_num=%0.4n binds_to=%A";
    char **buffer;

    // ==============================================
    // CODE SEGMENT 1: AFFINITY FORMAT
    // Get and Display Default Affinity Format
    // ==============================================
    nchars = omp_get_affinity_format(default_format, static_cast<size_t>(FORMAT_STORE));
    printf("Default Affinity Format is: %s\n", default_format);

    if (nchars >= FORMAT_STORE) {
        printf("Caution: Reported Format is truncated.  Increase\n");
        printf("        FORMAT_STORE to %d.\n", static_cast<int>(nchars + 1));
    }

    // Set Affinity Format
    omp_set_affinity_format(my_format);
    printf("Affinity Format set to: %s\n", my_format);

    // ==============================================
    // 【修复核心】用实际线程数分配缓冲区，而非CPU核心数
    // ==============================================
    // 读取环境变量设置的线程数（OMP_NUM_THREADS=4）
    n = omp_get_max_threads();
    // 显式设置并行线程数，确保和环境变量一致
    omp_set_num_threads(n);

    buffer = static_cast<char**>(malloc(sizeof(char*) * n));
    for (i = 0; i < n; i++) {
        buffer[i] = static_cast<char*>(malloc(sizeof(char) * BUFFER_STORE));
        // 【额外安全】初始化缓冲区为全0，避免野内存
        memset(buffer[i], 0, BUFFER_STORE);
    }

    // ==============================================
    // Capture Affinity using Affinity Format set above
    // Use max reduction to check size of buffer areas
    // ==============================================
    max_req_store = 0;
    #pragma omp parallel private(thrd_num, nchars) reduction(max:max_req_store)
    {
        if (omp_get_num_threads() > n) {
            exit(1); // safety: don't exceed # of buffers allocated
        }

        thrd_num = omp_get_thread_num();
        nchars = omp_capture_affinity(buffer[thrd_num], static_cast<size_t>(BUFFER_STORE), nullptr);
        if (nchars > max_req_store) {
            max_req_store = static_cast<int>(nchars);
        }

        // ... (thread work can be added here)
    }

    // Print affinities in thread number order
    for (i = 0; i < n; i++) {
        printf("thrd_num= %d, affinity: %s\n", i, buffer[i]);
    }

    /*
    // For 4 threads with OMP_PLACES='{0,1},{2,3},{4,5},{6,7}'
    // Format  host=%20H thrd_num=%0.4n binds_to=%A
    // affinity: host=hpc.cn567          thrd_num=0000 binds_to=0,1
    // affinity: host=hpc.cn567          thrd_num=0001 binds_to=2,3
    // affinity: host=hpc.cn567          thrd_num=0002 binds_to=4,5
    // affinity: host=hpc.cn567          thrd_num=0003 binds_to=6,7
    */

    // Check for possible truncation
    if (max_req_store >= BUFFER_STORE) {
        printf("Caution: Affinity string truncated.  Increase\n");
        printf("        BUFFER_STORE to %d\n", max_req_store + 1);
    }

    // Free allocated memory
    for (i = 0; i < n; i++) {
        free(buffer[i]);
    }
    free(buffer);

    return 0;
}