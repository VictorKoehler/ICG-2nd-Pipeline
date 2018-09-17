#include "main_extensions.h"


#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>



//-----------------------------------------------------------------------------


SpaceContainer e;

void MyGlDraw(void)
{
	//drawSpace(e);
	drawFreezedPreComputedSpace(e);
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

	buildMonkeyExample(&e);

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}
