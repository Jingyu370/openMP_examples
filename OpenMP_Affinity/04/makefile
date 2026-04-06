CXX = icpx
CXXFLAGS = -std=c++17 -qopenmp


TARGET = affinity_query1
SRC = affinity_query1.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

run: $(TARGET)
	export OMP_PLACES="{0,1,2,3},{4,5,6,7}" && \
	export OMP_NUM_THREADS=2,4 && \
	./$(TARGET)

clean:
	rm -f $(TARGET)