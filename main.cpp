#include "pipeline_extensions.h"


#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>



//-----------------------------------------------------------------------------


Scene e;

void MyGlDraw(void)
{
	clear(0, 0, IMAGE_WIDTH - 1, IMAGE_HEIGHT - 1);
	SphereExample_MyGlDraw(&e);
	drawFreezedPreComputedSpace(e);
	//drawSpace(e);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	buildSphereExample(&e);

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}
