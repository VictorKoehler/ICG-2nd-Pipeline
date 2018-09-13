#include <assimp/Importer.hpp> 	   // C++ importer interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

#include "objetos.h"


using Eigen::Vector4f;
using Eigen::Matrix4f;
using namespace std;

class Espaco
{
	Matrix4f view, projection, canonic, screen, summary;

	public:
	vector<Objeto> objetos;

	// file_name contém o nome do arquivo a ser carregado
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

};