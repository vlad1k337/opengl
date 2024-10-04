CFLAGS   = -Wall -Wextra
INCLUDES = -Iinclude/
LIBS     = -lglfw -lGL  
CC = g++

all: main.o glad.o
	$(CC) $(CFLAGS) -o main $^ $(LIBS) 

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp $(INCLUDES) 

glad.o: glad.c
	$(CC) $(CFLAGS) -o glad.o -c glad.c $(INCLUDES)

clean: 
	rm -f glad.o main.o main 
