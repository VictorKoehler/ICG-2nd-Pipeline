#include <assimp/Importer.hpp> 	   // C++ importer interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

using Eigen::Vector4f;
using Eigen::VectorXf;
using Eigen::Matrix4f;
using namespace std;


/*
	Cria uma instância de uma matriz tal que: [ x, y, z, (0; 0; 0; 1) ], sendo x, y, z vetores coluna.
*/
Matrix4f createBasis(Vector4f x, Vector4f y, Vector4f z)
{
	VectorXf vec1(16);
	Matrix4f m4;
	m4 << x, y, z, (Vector4f() << 0, 0, 0, 1).finished();
	return m4;
}

/*
	Transpõe uma chamada a createBasis(x, y, z).
*/
Matrix4f createTransposedBasis(Vector4f x, Vector4f y, Vector4f z)
{ 
	return createBasis(x, y, z).transpose();
}


/*
	Transpõe uma chamada a createBasis(x, y, z).
*/
Matrix4f translate(float x, float y, float z)
{
	Vector4f x(1, 0, 0, 2);
	Vector4f y(0, 1, 0, 3);
	Vector4f z(0, 0, 1, 4);
	return createTransposedBasis(x, y, z);
}



void printExample1()
{
	Vector4f x(1.0, 2.0, 3.0, 0.0);
	Vector4f y(4, 5, 6, 0);
	Vector4f z(7, 8, 9, 0);
	cout << createTransposedBasis(x, y, z) << endl;
}

void printExample2()
{
	Vector4f x(1, 0, 0, 2);
	Vector4f y(0, 1, 0, 3);
	Vector4f z(0, 0, 1, 4);
	cout << createTransposedBasis(x, y, z) << endl;
}