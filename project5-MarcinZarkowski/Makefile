CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2

PROG ?= main
OBJS = Dish.o KitchenStation.o StationManager.o main.o

all: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS)
	chmod +x $(PROG)
clean:
	rm -rf $(EXEC) *.o *.out main 

rebuild: clean all