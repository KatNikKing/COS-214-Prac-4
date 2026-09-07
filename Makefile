CXX := g++
CXXFLAGS = -std=c++11 -g -Wall -Werror

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := taskforge

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./taskforge

gdb: $(TARGET)
	gdb ./taskforge

valgrind: $(TARGET)
	valgrind --leak-check=full --keep-stacktraces=alloc-and-free --track-origins=yes ./taskforge
