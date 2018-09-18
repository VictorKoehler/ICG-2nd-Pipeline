#include "pipeline_extensions.h"


#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>



//-----------------------------------------------------------------------------


Scene e;
char example = 0;

void MyGlDraw(void)
{
	clear(0, 0, IMAGE_WIDTH - 1, IMAGE_HEIGHT - 1);
	switch (example)
	{
		case 's':
			SphereExample_MyGlDraw(&e);
			break;
		case 'm':
			MonkeyExample_MyGlDraw(&e);
			break;
		case 'c':
			CubeExample_MyGlDraw(&e);
			break;
	}
	drawFreezedPreComputedSpace(e);
	//drawSpace(e);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (argv[1][1] == 'h')
		{
			printf("%s -[h|s|m|c][r][a]\n   Where:\n"
			"   h: This help\n"
			"   s: Sphere example\n"
			"   m: Monkey example\n"
			"   c: Cube example\n"
			"   r: (Optional)Do not Rotate Examples (if this letter is present)\n"
			"   a: (Optional)Draw Line Axis (if this letter is present)\n",
			argv[0]);
			return 0;
		}
		else
		{
			example = argv[1][1];
			doNotRotate = (argv[1][2] == 'r');
			doNotDrawAxis = !(argv[1][2] == 'a' || (argv[1][2] != '\0' && argv[1][3] == 'a'));
			switch (example)
			{
				case 's':
					buildSphereExample(&e);
					break;
				case 'm':
					buildMonkeyExample(&e);
					break;
				case 'c':
					buildCubeExample(&e);
					break;
			}
		}
	}
	// e.view *= createScaleMatrix(1.3, 1.1, 1, 0.4);
	// e.viewport *= createRotationAboutYMatrix(0.7);
	// e.buildPipeline();
	// e.invalidateAllObjects();


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
