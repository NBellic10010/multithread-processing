CC = g++
CFLAGS = --std=c++11

objects = Simulation.o Process.o Queue.o Node.o ListItem.o Event.o 

all: A2main.o $(objects)
	$(CC) $(CFLAGS) -o A2 $< $(objects)

A2main.o: A2main.cpp Simulation.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

Simulation.o: Simulation.cpp Event.cpp Process.cpp Queue.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

Process.o: Process.cpp ListItem.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

Queue.o: Queue.cpp Node.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

ListItem.o: ListItem.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

Node.o: Node.cpp ListItem.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

Event.o: Event.cpp Queue.cpp Node.cpp ListItem.cpp Process.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm *.o