CXX = g++

CXXFLAGS = -std=c++11 -Wall -g

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

taskforge: $(OBJS)
	$(CXX) $(CXXFLAGS) -o taskforge $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:

	rm -f $(OBJS) taskforge

.PHONY: clean