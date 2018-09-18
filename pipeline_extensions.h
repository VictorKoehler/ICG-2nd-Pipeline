#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>



#ifndef HEADER_GUARD_ESPACO
#define HEADER_GUARD_ESPACO

#include "scene.h"

#endif

#include "examples.h"



using namespace std;



inline Point toPoint(Eigen::Vector4f v)
{
	Point p;
	p.x = (int)(v(0) / v(3));
	p.y = (int)(v(1) / v(3));
	return p;
}

inline void drawSimpleLine(Point p0, Point p1, Color c)
{
	Line l;
	l.p0.p = p0;
	l.p1.p = p1;
	l.p0.c = c;
	l.p1.c = c;
	DrawLine(l);
}


/**
 * Desenha o objeto o na tela usando a matriz ModelViewProjectionViewport mVPV
 **/
inline void drawObject(ObjectModel o, Matrix4f mVPV)
{
    for (vector<Vertex>::iterator it = o.vertices.begin(); it != o.vertices.end(); it++)
    {
        Point p0 = toPoint(mVPV * it->v0), p1 = toPoint(mVPV * it->v1), p2 = toPoint(mVPV * it->v2);
        drawSimpleLine(p0, p1, o.preferredColor);
        drawSimpleLine(p0, p2, o.preferredColor);
        drawSimpleLine(p1, p2, o.preferredColor);
    }
}


/*
	Desenha na tela o espaço especificado.
	Este método apenas percorre todos os objetos do espaço, chamando drawObject.
*/
void drawSpace(Scene e)
{
	for (vector<ObjectModel>::iterator itb = e.objects.begin(); itb != e.objects.end(); itb++)
	{
        drawObject(*itb, e.pipeline * itb->model);
	}
}








inline Point toPoint(Eigen::DenseCoeffsBase<MatrixXf> c)
{
	Point p;
	p.x = (int)(c(0) / c(3));
	p.y = (int)(c(1) / c(3));
	return p;
}


/*
	Desenha na tela um espaço na qual todos os vértices já tenham passado pela fase de processamento,
	isto é, possuem, cada um, a matriz precomputed calculada.
	Isto é especialmente útil quando a câmera está parada e nem todos os objetos estão se movendo,
	reduzindo a carga de redesenhar toda a tela.
	Consulte MonkeyExample_MyGlDraw e SphereExample_MyGlDraw para exemplo de implementação e referência.
*/
void drawFreezedPreComputedSpace(Scene e)
{
	for (vector<ObjectModel>::iterator itb = e.objects.begin(); itb != e.objects.end(); itb++)
	{
		int i = 0, cols = itb->vertices.size()*3;
		while (i < cols)
		{
			Point 	p0 = toPoint(itb->precomputed.col(i++)),
					p1 = toPoint(itb->precomputed.col(i++)),
					p2 = toPoint(itb->precomputed.col(i++));
			drawSimpleLine(p0, p1, itb->preferredColor);
			drawSimpleLine(p0, p2, itb->preferredColor);
			drawSimpleLine(p1, p2, itb->preferredColor);
		}
	}
}