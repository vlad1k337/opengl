CFLAGS       = -Wall -Wextra
INCLUDES     = -Iinclude/
LIBS   	     = -lglfw -lGL  
LOADER_FLAGS = -O3 -funroll-loops
CC = g++

all: main.o glad.o 
	$(CC) $(CFLAGS) $(LOADER_FLAGS) -o main $^ $(LIBS) $(INCLUDES) 

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp $(INCLUDES) 

glad.o: glad.c
	$(CC) $(CFLAGS) -o glad.o -c glad.c $(INCLUDES)

clean: 
	rm -f glad.o main.o main 
