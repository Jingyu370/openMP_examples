#include <cstdio>
#include <omp.h>

void socket_init(int socket_num);

int main()
{
    int n_sockets, socket_num;

    // 1. 启用嵌套并行（等价于环境变量 OMP_NESTED=true）
    omp_set_nested(1);
    // 2. 设置最大活跃并行层级为 2（等价于 OMP_MAX_ACTIVE_LEVELS=2）
    omp_set_max_active_levels(2);

    // 3. 获取系统的 Place 数量（即 CPU 插槽数量）
    n_sockets = omp_get_num_places();

    // 4. 外层并行区域
    //线程数 = 插槽数量 (n_sockets)
    //使用 proc_bind(spread)：将线程均匀分散到不同的 Place (插槽)
    //private(socket_num)：每个线程私有一个 socket_num 变量
    #pragma omp parallel num_threads(n_sockets) proc_bind(spread) private(socket_num)
    {
        // 获取当前线程所绑定的 Place (插槽) 编号
        socket_num = omp_get_place_num();
        
        // 进入嵌套并行，执行插槽初始化工作
        socket_init(socket_num);
    }

    return 0;
}

// 插槽工作函数
void socket_init(int socket_num)
{
    int n_procs;

    // 1. 获取当前插槽 (socket_num) 内的核心数量
    n_procs = omp_get_place_num_procs(socket_num);

    // 2. 内层嵌套并行
    //线程数 = 当前插槽的核心数量 (n_procs)
    //proc_bind(close)：将线程紧密绑定在核心上，最大化缓存亲和性
    #pragma omp parallel num_threads(n_procs) proc_bind(close)
    {
        printf("Reporting in from socket num, thread num: %d %d\n", 
               socket_num, omp_get_thread_num());
    }
}