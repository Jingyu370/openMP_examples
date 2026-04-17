void atomic_wrong ()
{
  union { int n; float x; } u; // 定义一个共用体（union），int和float共享同一块内存

#pragma omp parallel
  {
#pragma omp atomic update
    u.n++; // 原子操作：以int类型访问并更新共用体的n成员

#pragma omp atomic update
    u.x += 1.0; // 原子操作：以float类型访问并更新共用体的x成员
  }
}
/* Incorrect because the atomic constructs reference the same location
   through incompatible types */
// 【错误原因】：这些atomic指令通过不兼容的类型，引用了同一个内存地址

void atomic_wrong2 ()
{
  int x;       // 定义int变量x
  int *i;      // 定义int*指针
  float *r;    // 定义float*指针

  i = &x;                  // i指向x的地址（按int类型访问）
  r = (float *)&x;         // 强制类型转换：让r也指向x的地址，但按float类型访问

#pragma omp parallel
  {
#pragma omp atomic update
    *i += 1;    // 原子操作：以int类型更新*x

#pragma omp atomic update
    *r += 1.0;  // 原子操作：以float类型更新*x
  }
}
/* Incorrect because the atomic constructs reference the same location
   through incompatible types */
// 【错误原因】：这些atomic指令通过不兼容的类型，引用了同一个内存地址