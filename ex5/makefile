CC=g++
FLAGS= -g -Wall 

all: runC runS

runC: client.o
	$(CC) $(FLAGS) -o runC client.o 

runS: server.o
	$(CC) $(FLAGS) -o runS server.o -pthread

client.o: client.cpp 
	$(CC) $(FLAGS) -c client.cpp

server.o: server.cpp 
	$(CC) $(FLAGS) -c server.cpp 


.PHONY: clean all

clean:
	rm -f *.o runC runS