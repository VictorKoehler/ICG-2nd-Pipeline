#include <assimp/Importer.hpp> 	   // C++ importer interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

#include "objetos.h"
#include "common.h"


using Eigen::Vector4f;
using Eigen::VectorXf;
using Eigen::Matrix4f;
using namespace std;



class Espaco
{
	Matrix4f view, projection, canonic, screen, summary;

	public:
	vector<Objeto> objetos;

	/*	Carrega um objeto no espaço. */
	int loadObject(const std::string &file_name)
	{
        Objeto o;
        int r = o.loadMesh(file_name);
        if (r == EXIT_SUCCESS)
        {
            objetos.push_back(o);
        }
		return r;
	}

	void setCameraByDirection(Vector4f position, Vector4f direction, Vector4f up)
	{
		// Vector4f camera_z = direction.normalized() * (-1);
		// Vector4f camera_x = up.cross(camera_z).normalized();
		// Vector4f camera_y = camera_z.cross(camera_x).normalized();

		// Matrix4f Bt = createTransposedBasis(camera_x, camera_y, camera_z);

		
	}

	/* 
		Posiciona a câmera apontada para a posição indicada em lookAt.
		Este método simplesmente chama setCameraByDirection com lookAt recalculado.
	*/
	void setCameraByLookAt(Vector4f position, Vector4f lookAt, Vector4f up)
	{
		setCameraByDirection(position, lookAt - position, up);
	}

};