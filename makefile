CC=g++
CFLAGS=--std=c++11

objects = Event.o Simulation.o # .. etc .. put a list of your .o files here  

# this rule will build A2 as the executable from the object files
all: A2main.o $(objects)
        $(CC) $(CFLAGS) -o A2 $< $(objects)

# this rule will build a .o file from a .cpp file. 
%.o: %.cpp
        $(CC) -c -o $@ $< $(CFLAGS)
Simulation.o: Simulation.cpp Process.o Event.o
        $(CC) $(CFLAGS) -c 
Event.o: Event.cpp
        $(CC) $(CFLAGS) -c Event.cpp

Process.o: Process.cpp 
        $(CC) $(CFLAGS) -c Process.cpp
Queue.o: Queue.cpp ListItem.o Node.o
        $(CC) $(CFLAGS) Queue.cpp ListItem.o Node.o 
Node.o: Node.cpp ListItem.o
        $(CC) $(CFLAGS) Node.cpp ListItem.o
ListItem.o: ListItem.cpp
        $(CC) $(CFLAGS) ListItem.cpp 
