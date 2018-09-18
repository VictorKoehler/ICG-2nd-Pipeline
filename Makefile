CC = g++

all:
	$(CC) main.cpp -lglut -lGLU -lGL -I. -lassimp -o cgprog && $(CC) opengl_test.cpp -lglut -lGLU -lGL -I. -lassimp -o opengl_test

clean:
	rm cgprog opengl_test

