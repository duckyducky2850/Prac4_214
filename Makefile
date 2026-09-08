
# Target executable, default name
TARGET= taskforge

# Compiler flags
CXXFLAG = -std=c++11 -g -Wall -Werror 

##DO NOT TOUCH----------------------------------------------------------------------

# Compiler
CXX = g++

CXXFLAGS = -std=c++11 -Wall -g

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

taskforge: $(OBJS)
	$(CXX) $(CXXFLAGS) -o taskforge $(OBJS)

OBJS=$(patsubst src/%,obj/%,$(OBJSTEMP))

all: bin/$(TARGET)


bin/$(TARGET): $(OBJS) $(SRCS) |bin
	$(CXX) $(CXXFLAGS) -o bin/$(TARGET) $(OBJS)


obj/%.o: src/%.cpp | $(OBJDIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: bin/$(TARGET) $(SRCS) $(OBJS) 
	./bin/$(TARGET)

clean:
	rm -f $(OBJS) bin/$(TARGET) 

# Run valgrind
valgrind:bin/$(TARGET) $(SRCS) $(OBJS) 
	valgrind --leak-check=full ./bin/$(TARGET)

	rm -f $(OBJS) taskforge

.PHONY: clean