CFLAGS = -g

all: main

clean:
	rm -f *.o main

main : main.o
	gcc $^ -o main -lGL -lGLU -lglut -lm

main.o : main.c

