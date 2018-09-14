#include "main.h"
#include "espaco.h"
#include <vector>

#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>



//-----------------------------------------------------------------------------


Espaco e;

Point toPoint(Eigen::Vector4f v)
{
	Point p;
	p.x = (int)(v(0) / v(3));
	p.y = (int)(v(1) / v(3));
	return p;
}

void drawSimpleLine(Point p0, Point p1, Color c)
{
	Line l;
	l.p0.p = p0;
	l.p1.p = p1;
	l.p0.c = c;
	l.p1.c = c;
	DrawLine(l);
}

void MyGlDraw(void)
{
	for (vector<Objeto>::iterator itb = e.objetos.begin(); itb != e.objetos.end(); itb++)
	{
		for (vector<Vertice>::iterator it = itb->vertices.begin(); it != itb->vertices.end(); it++)
		{
			Point p0 = toPoint(e.pipeline * it->v0), p1 = toPoint(e.pipeline * it->v1), p2 = toPoint(e.pipeline * it->v2);
			drawSimpleLine(p0, p1, itb->preferredColor);
			drawSimpleLine(p0, p2, itb->preferredColor);
			drawSimpleLine(p1, p2, itb->preferredColor);
		}
	}
}

void buildMonkeyExample()
{
	double x = 1.4, y = 1, z = 2.2, l = 2;
	Vector3f pos(x, y, z);
	Vector3f lookat(0, 0, 0);
	Vector3f up(0, 1, 0);
	e.buildCameraByLookAt(pos, lookat, up);

	e.buildProjectionMatrix(1);

	e.buildViewportMatrix(IMAGE_WIDTH, IMAGE_HEIGHT);

	e.buildPipeline();

	Vertice v;
	v.v0 = v.v1 = Vector4f(0, 0, 0, 1);

	Objeto o0;
	v.v2 = Vector4f(x, 0, 0, 1);
	o0.vertices.push_back(v);
	o0.preferredColor.g = o0.preferredColor.b = 0;
	e.objetos.push_back(o0);

	Objeto o1;
	v.v2 = Vector4f(0, y, 0, 1);
	o1.vertices.push_back(v);
	o1.preferredColor.r = o1.preferredColor.b = 0;
	e.objetos.push_back(o1);

	Objeto o2;
	v.v2 = Vector4f(0, 0, z, 1);
	o2.vertices.push_back(v);
	o2.preferredColor.r = o2.preferredColor.g = 0;
	e.objetos.push_back(o2);


	/*
	Objeto o3;
	v.v0 = v.v1 = Vector4f(0.1, 0.1, 0.1, 1);

	v.v2 = Vector4f(l, l, 0, 1);
	v.v1 = Vector4f(l, 0, 0, 1);
	o3.vertices.push_back(v);
	v.v1 = Vector4f(0, l, 0, 1);
	o3.vertices.push_back(v);

	v.v2 = Vector4f(l, 0, l, 1);
	v.v1 = Vector4f(l, 0, 0, 1);
	o3.vertices.push_back(v);
	v.v1 = Vector4f(0, 0, l, 1);
	o3.vertices.push_back(v);

	v.v2 = Vector4f(0, l, l, 1);
	v.v1 = Vector4f(0, l, 0, 1);
	o3.vertices.push_back(v);
	v.v1 = Vector4f(0, 0, l, 1);
	o3.vertices.push_back(v);

	o3.preferredColor.r = o3.preferredColor.g = o3.preferredColor.b = 128;
	e.objetos.push_back(o3);
	*/


	e.loadObject("monkey_head2.obj");
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

	buildMonkeyExample();

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}
