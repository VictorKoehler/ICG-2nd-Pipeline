#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::VectorXf;
using Eigen::Matrix4f;
using Eigen::MatrixXf;
using namespace std;


Vector4f toHomogeneous(Vector3f v)
{
	return (Vector4f() << v, 1).finished();
}

Vector4f toHomogeneous(Vector3f v, float d)
{
	return (Vector4f() << v, d).finished();
}




/*
	Cria uma instância de uma matriz tal que: [ x, y, z, (0; 0; 0; 1) ], sendo x, y, z vetores coluna.
*/
Matrix4f createBasis(Vector3f x, Vector3f y, Vector3f z)
{
	Matrix4f m4;
	m4 << toHomogeneous(x, 0), toHomogeneous(y, 0), toHomogeneous(z, 0), (Vector4f() << 0, 0, 0, 1).finished();
	return m4;
}

/*
	Transpõe uma chamada a createBasis(x, y, z).
*/
Matrix4f createTransposedBasis(Vector3f x, Vector3f y, Vector3f z)
{ 
	return createBasis(x, y, z).transpose();
}

/*
	Cria uma instância de uma matriz tal que: [ x, y, z, (0; 0; 0; 1) ], sendo x, y, z vetores coluna.
*/
Matrix4f createBasis_4dv(Vector4f x, Vector4f y, Vector4f z)
{
	Matrix4f m4;
	m4 << x, y, z, (Vector4f() << 0, 0, 0, 1).finished();
	return m4;
}

/*
	Transpõe uma chamada a createBasis(x, y, z).
*/
Matrix4f createTransposedBasis_4dv(Vector4f x, Vector4f y, Vector4f z)
{ 
	return createBasis_4dv(x, y, z).transpose();
}




/*
	Obtém uma matriz de translação dados x, y, z, w.
*/
Matrix4f createScaleMatrix(float x, float y, float z, float w)
{
	return (Matrix4f() <<
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, w).finished();
}

/*
	Obtém uma matriz de translação dados x, y, z.
	Adiciona automaticamente 1 na coordenada w.
*/
Matrix4f createScaleMatrix(float x, float y, float z)
{
	return createScaleMatrix(x, y, z, 1);
}

/*
	Obtém uma matriz de translação dado um vetor.
*/
Matrix4f createScaleMatrix(Vector4f v)
{
	return createScaleMatrix(v(0), v(1), v(2), v(3));
}

/*
	Obtém uma matriz de translação dado um vetor.
	Adiciona automaticamente 1 na coordenada w.
*/
Matrix4f createScaleMatrix_3dv(Vector3f v)
{
	return createScaleMatrix(v(0), v(1), v(2), 1);
}




/*
	Obtém uma matriz de translação dados x, y, z, w.
*/
Matrix4f createTranslationMatrix(float x, float y, float z, float w)
{
	return (Matrix4f() <<
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, w).finished();
	// Vector4f xv(1, 0, 0, x);
	// Vector4f yv(0, 1, 0, y);
	// Vector4f zv(0, 0, 1, z);
	// return createTransposedBasis(xv, yv, zv);
}

/*
	Obtém uma matriz de translação dados x, y, z.
	Adiciona automaticamente 1 na coordenada w.
*/
Matrix4f createTranslationMatrix(float x, float y, float z)
{
	return createTranslationMatrix(x, y, z, 1);
}

/*
	Obtém uma matriz de translação dado um vetor.
*/
Matrix4f createTranslationMatrix(Vector4f v)
{
	return (Matrix4f() << MatrixXf::Identity(4,3), v).finished();
	// Vector4f xv(1, 0, 0, x);
	// Vector4f yv(0, 1, 0, y);
	// Vector4f zv(0, 0, 1, z);
	// return createTransposedBasis(xv, yv, zv);
}

/*
	Obtém uma matriz de translação dado um vetor.
	Adiciona automaticamente 1 na coordenada w.
*/
Matrix4f createTranslationMatrix_3dv(Vector3f v)
{
	return createTranslationMatrix(toHomogeneous(v));
	// Vector4f xv(1, 0, 0, x);
	// Vector4f yv(0, 1, 0, y);
	// Vector4f zv(0, 0, 1, z);
	// return createTransposedBasis(xv, yv, zv);
}












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