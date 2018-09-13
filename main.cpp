#include "main.h"
#include "espaco.h"


//-----------------------------------------------------------------------------
void MyGlDraw(void)
{

}


//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	example_testPipeline();

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
