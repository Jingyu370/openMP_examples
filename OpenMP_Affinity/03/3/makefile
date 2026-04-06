CXX = icpx
CXXFLAGS = -std=c++17 -qopenmp -O2

# 目标可执行文件名
TARGET = affinity3

# 源文件
SRC = affinity_display3.cpp

# 默认目标：编译
all: $(TARGET)

# 编译规则
$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

# 运行目标（自动设置环境变量）
run: $(TARGET)
	export OMP_PROC_BIND=TRUE && \
	export OMP_NUM_THREADS=4 && \
	export OMP_PLACES="{0,1},{2,3},{4,5},{6,7}" && \
	./$(TARGET)

# 清理编译产物
clean:
	rm -f $(TARGET)

# 调试编译（带调试信息）
debug: CXXFLAGS += -g
debug: $(TARGET)