CC = g++

all:
	$(CC) main.cpp -lglut -lGLU -lGL -I. -lassimp -o cgprog

clean:
	rm cgprog

