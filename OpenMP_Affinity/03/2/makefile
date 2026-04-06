CXX = icpx

# 编译选项：必须加 -fopenmp 才能用 OpenMP
CXXFLAGS = -std=c++17 -qopenmp

# 最终生成的可执行文件名字
TARGET = affinity

# 要编译的源代码文件
SRC = affinity_display2.cpp

# 默认目标：编译程序
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

# 清理编译产物
clean:
	rm -f $(TARGET)

# 运行程序（自动设置环境变量）
run: $(TARGET)
	export OMP_PROC_BIND=TRUE && \
	export OMP_NUM_THREADS="2,4" && \
	export OMP_PLACES="{0,2,4,6},{1,3,5,7}" && \
	export OMP_AFFINITY_FORMAT="nest_level= %L, parent_thrd_num= %a, thrd_num= %n, thrd_affinity= %A" && \
	./$(TARGET)