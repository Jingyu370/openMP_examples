
CC = icpx

# 编译选项：开启 OpenMP + 优化
CFLAGS = -qopenmp -O2 -Wall

# 目标程序名
TARGET = affinity_display1

# 源文件
SRC = affinity_display1.cpp

# 默认目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

# 清理
clean:
	rm -f $(TARGET)

# 运行（自动设置环境变量）
run: export OMP_PROC_BIND=TRUE
run: export OMP_DISPLAY_AFFINITY=TRUE
run: $(TARGET)
	./$(TARGET)