
# Target executable, default name
TARGET= taskforce

# Compiler flags
CXXFLAG = -std=c++11 -Wall -Werror 

##DO NOT TOUCH----------------------------------------------------------------------

# Compiler
CXX = g++

# all method names
.PHONY: all clean run valgrind

#Don't delete .o
.PRECIOUS: obj/%.o

# Source files
SRCS=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

# Object files
OBJSTEMP = $(SRCS:.cpp=.o)

OBJS2=$(patsubst src/%,%,$(OBJSTEMP))

OBJS3=$(subst /, ,$(OBJS2))

OBJ_DIR=$(sort $(patsubst %.o,,$(OBJS3)))

INC_FLAGS := $(addprefix -Isrc/, $(OBJ_DIR))
CXXFLAGS=$(CXXFLAG) -I. -Isrc $(INC_FLAGS)

OBJS=$(patsubst src/%,obj/%,$(OBJSTEMP))

all: $(TARGET) run


$(TARGET): $(OBJS) $(SRCS) |bin
	$(CXX) $(CXXFLAGS) -o bin/$(TARGET) $(OBJS)


obj/%.o: src/%.cpp | obj/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET) $(SRCS) $(OBJS) 
	./bin/$(TARGET)

clean:
	rm -f $(OBJS) bin/$(TARGET) 

# Run valgrind
valgrind:$(TARGET) $(SRCS) $(OBJS) 
	valgrind --leak-check=full ./bin/$(TARGET)

#create directory if needed
obj/$(OBJ_DIR):
	mkdir -p obj/$(OBJ_DIR)

bin:
	mkdir -p bin
	
print-%:
	@echo $* = $($*)