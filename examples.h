#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>


#ifndef HEADER_GUARD_ESPACO
#define HEADER_GUARD_ESPACO

#include "scene.h"

#endif


using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::VectorXf;
using Eigen::Matrix4f;
using Eigen::MatrixXf;
using namespace std;



bool doNotRotate = false, doNotDrawAxis = false;


/*
	Teste de Criação de Base.
*/
void example_printBasis1()
{
	Vector3f x(1.0, 2.0, 3.0);
	Vector3f y(4, 5, 6);
	Vector3f z(7, 8, 9);
	cout << createTransposedBasis(x, y, z) << endl;
}
/*
	Teste de Criação de Base.
*/
void example_printBasis2()
{
	Vector4f x(1, 0, 0, 2);
	Vector4f y(0, 1, 0, 3);
	Vector4f z(0, 0, 1, 4);
	cout << createTransposedBasis_4dv(x, y, z) << endl;
}

/*
	Teste das diferentes implementações da translação.
	Deve imprimir 3 matrizes iguais.
*/
void example_printTranslate()
{
	Vector4f v4(2, 3, 4, 1);
	Vector3f v3(2, 3, 4);
	cout 	<< createTranslationMatrix(v4) << endl << endl
		 	<< createTranslationMatrix_3dv(v3) << endl << endl
			<< createTranslationMatrix(2, 3, 4) << endl;
}

/*
	Teste das diferentes implementações da translação.
	Deve imprimir 3 matrizes iguais.
*/
void example_printScaleTest()
{
	Vector4f v(2, 3, 4, 1);
	cout << createScaleMatrix(v) << endl << endl;
}





/*
	Pequeno teste da matriz View, com base no arquivo disponibilizado pelo professor:
	camera_pos    = [1.3; 2.1; 2.5];  # Posicao da camera no universo.
	camera_lookat = [0; 0; 0];  # Ponto para onde a camera esta olhando.
	camera_up     = [0; 1; 0];  # 'up' da camera no espaco do universo.
*/
void example_testCamera()
{
	Vector3f pos(1.3, 2.1, 2.5);
	Vector3f lookat(0, 0, 0);
	Vector3f up(0, 1, 0);

	Scene e;
	e.buildCameraByLookAt(pos, lookat, up);

	cout << e.view << endl;
}

/*
	Pequeno teste da matriz Projection, com d = 1;
*/
void example_testProjection()
{
	Scene e;
	e.buildProjectionMatrix(1);

	cout << e.projection << endl;
}

/*
	Pequeno teste do pipeline, com base no arquivo disponibilizado pelo professor.
*/
Scene example_testPipeline()
{
	Scene e;

	Vector3f pos(1.3, 2.1, 2.5);
	Vector3f lookat(0, 0, 0);
	Vector3f up(0, 1, 0);
	e.buildCameraByLookAt(pos, lookat, up);

	e.buildProjectionMatrix(1);

	e.buildViewportMatrix(512, 512);

	e.buildPipeline();

	//cout << e.viewport << endl << endl << e.projection << endl << endl << e.view << endl << endl;

	cout << e.pipeline << endl;
	return e;
}



/*
	Dado um espaço-container, desenha os eixos-x-y-z como objetos,
		nas cores vermelho, verde e azul respectivamente.
	Os parâmetros do tipo float descrevem o tamanho da linha desenhada no eixo.
*/
void insertAxisLines(Scene *e, float x, float y, float z)
{
	Vertex v;
	v.v0 = v.v1 = Vector4f(0, 0, 0, 1);

	ObjectModel o0;
	v.v2 = Vector4f(x, 0, 0, 1);
	o0.vertices.push_back(v);
	o0.preferredColor.g = o0.preferredColor.b = 0;
	e->objects.push_back(o0);

	ObjectModel o1;
	v.v2 = Vector4f(0, y, 0, 1);
	o1.vertices.push_back(v);
	o1.preferredColor.r = o1.preferredColor.b = 0;
	e->objects.push_back(o1);

	ObjectModel o2;
	v.v2 = Vector4f(0, 0, z, 1);
	o2.vertices.push_back(v);
	o2.preferredColor.r = o2.preferredColor.g = 0;
	e->objects.push_back(o2);
}



/*
	Constrói o exemplo de importação do macaco.
	Câmera: Posição = (1.4, 1, 2.2)
			LookAt  = (0, 0, 0)
			Up 		= (0, 1, 0)
*/
void buildMonkeyExample(Scene *e)
{
	double x = 1.4, y = 1, z = 2.2, l = 2;
	Vector3f pos(x, y, z);
	Vector3f lookat(0, 0, 0);
	Vector3f up(0, 1, 0);
	e->buildCameraByLookAt(pos, lookat, up);

	e->buildProjectionMatrix(1);

	e->buildViewportMatrix(IMAGE_WIDTH, IMAGE_HEIGHT);

	e->buildPipeline();

	if (!doNotDrawAxis)
		insertAxisLines(e, x, 2*y, z);
	/*
	ObjectModel o3;
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
	e->objects.push_back(o3);
	*/


	e->loadObject("monkey_head2.obj");
	e->invalidateAllObjects();
}

/*
	MyGlDraw sugerido do exemplo do macaco.
	Neste exemplo, apenas a figura do macaco permanece girando, enquanto os demais objetos,
	isto é, as linhas dos eixos coordenados, bem como a câmera, permanecem estáticos.
	Este método tira proveito desta configuração e ignora os cálculos destas linhas,
	usando apenas uma matriz do pipeline guardada como "cache" destes objetos,
	enquanto atualiza a matriz (todo o pipeline) apenas do macaco.
*/
void MonkeyExample_MyGlDraw(Scene* e)
{
	// Rotaciona o macaco.
	if (!doNotRotate)
		(e->objects.end() - 1)->model *= createRotationAboutXMatrix(0.01);

	// Atualiza a matriz cache do pipeline do macaco.
	(e->objects.end() - 1)->invalidatePreComputedMatrix(e->pipeline, false);

	// Esta prática evita a chamada do seguinte método.
	//e->invalidateAllObjects();
}



/*
	Constrói o exemplo de importação da esfera.
*/
void buildSphereExample(Scene *e)
{
	buildMonkeyExample(e);
	e->objects.pop_back();
	e->loadObject("Esfera.obj");
	e->invalidateAllObjects();
}

/*
	MyGlDraw sugerido do exemplo do cubo.
	Neste exemplo, apenas a figura do cubo permanece girando, enquanto os demaimacacomacacos objetos,
	isto é, as linhas dos eixos coordenados, bem como a câmera, permanecem estáticos.
	Este método tira proveito desta configuração e ignora os cálculos destas linhas,
	usando apenas uma matriz do pipeline guardada como "cache" destes objetos,
	enquanto atualiza a matriz (todo o pipeline) apenas do cubo.
*/
void SphereExample_MyGlDraw(Scene* e)
{
	if (!doNotRotate)
		(e->objects.end() - 1)->model *= createRotationAboutXMatrix(0.01) * createRotationAboutYMatrix(0.01);

	// Atualiza a matriz cache do pipeline do cubo.
	(e->objects.end() - 1)->invalidatePreComputedMatrix(e->pipeline, false);

	// Esta prática evita a chamada do seguinte método.
	//e->invalidateAllObjects();
}





float cube[] = {
-1, -1, -1, 1,
-1, -1,  1, 1,
-1, -1,  1, 1,

-1, -1, -1, 1,
 1, -1, -1, 1,
 1, -1, -1, 1,

-1, -1,  1, 1,
-1, -1,  1, 1,
 1, -1,  1, 1,

 1, -1, -1, 1,
 1, -1, -1, 1,
 1, -1,  1, 1,

-1,  1, -1, 1,
-1,  1, -1, 1,
-1,  1,  1, 1,

-1,  1, -1, 1,
-1,  1, -1, 1,
 1,  1, -1, 1,

-1,  1,  1, 1,
-1,  1,  1, 1,
 1,  1,  1, 1,

 1,  1, -1, 1,
 1,  1,  1, 1,
 1,  1,  1, 1,

-1, -1, -1, 1,
-1,  1, -1, 1,
-1,  1, -1, 1,

-1, -1,  1, 1,
-1, -1,  1, 1,
-1,  1,  1, 1,

 1, -1, -1, 1,
 1, -1, -1, 1,
 1,  1, -1, 1,

 1, -1,  1, 1,
 1,  1,  1, 1,
 1,  1,  1, 1
 };

/*
	Constrói o mesmo cubo do exemplo do material fornecido pelo docente, pipeline.m
*/
void buildCubeExample(Scene *e)
{
	Vector3f pos(1.3, 2.1, 2.5);
	Vector3f lookat(0, 0, 0);
	Vector3f up(0, 1, 0);
	e->buildCameraByLookAt(pos, lookat, up);

	e->buildProjectionMatrix(1);

	e->buildViewportMatrix(IMAGE_WIDTH, IMAGE_HEIGHT);

	e->buildPipeline();

	if (!doNotDrawAxis)
		insertAxisLines(e, 3, 3, 3);


	ObjectModel o;
	Vertex v;
	for (int i = 0; i < 144; i += 12)
	{
		Eigen::Map<Vector4f> v0(cube + i), v1(cube + i + 4), v2(cube + i + 8);
		v.v0 = v0;
		v.v1 = v1;
		v.v2 = v2;
		o.vertices.push_back(v);
	}
	e->objects.push_back(o);

	e->invalidateAllObjects();
}

/*
	MyGlDraw sugerido do exemplo.
*/
void CubeExample_MyGlDraw(Scene* e)
{
	if (!doNotRotate)
		(e->objects.end() - 1)->model *= createRotationAboutXMatrix(0.01) * createRotationAboutYMatrix(0.01);
	(e->objects.end() - 1)->invalidatePreComputedMatrix(e->pipeline, false);
}