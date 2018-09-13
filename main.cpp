#include "main.h"
#include "espaco.h"


//-----------------------------------------------------------------------------
void MyGlDraw(void)
{

}


//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	printExample2();
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}
