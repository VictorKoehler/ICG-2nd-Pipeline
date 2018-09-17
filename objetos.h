#include <assimp/Importer.hpp> 	   // C++ importer interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

#include "main.h"


using Eigen::Vector4f;
using Eigen::Matrix4f;
using Eigen::MatrixXf;
using namespace std;




typedef struct
{
	Vector4f v0, v1, v2;
}Vertex;



class ObjectModel
{
	//bool matrixed;

	void init()
	{
		//matrixed = false;
		model.setIdentity();
		preferredColor.r = preferredColor.g = preferredColor.b = 255;
	}

	public:
	ObjectModel()
	{
		init();
	}

	ObjectModel(const std::string &file_name)
	{
		init();
		loadMesh(file_name);
	}

	Color preferredColor;
	vector<Vertex> vertices; // Guardamos os vertices
	Matrix4f model; // Por conveniência, guardamos a model de cada objeto carregado.
	
	/*
		Aceleração: armazena uma matriz de vértices (4xV), sendo três-a-três um triângulo.
		precomputed é destinado a computação completa de Pipeline * Model * Vertices.
		precomputed_model é destinado a computação parcial de Model * Vertices.
	*/
	MatrixXf precomputed, precomputed_model;


	/*
		Atualiza a matriz precomputed.
		Se updateModel for true, a matriz precomputed_model também será atualizada (mais lento).
	*/
	inline void invalidatePreComputedMatrix(Matrix4f pipeline, bool updateModel)
	{
		MatrixXf vectors(4, vertices.size() * 3);
		int colv = 0;
		for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			vectors.col(colv++) = it->v0;
			vectors.col(colv++) = it->v1;
			vectors.col(colv++) = it->v2;
		}
		if (updateModel)
		{
			precomputed_model = model * vectors;
			precomputed = pipeline * precomputed_model;
		}
		else
		{
			precomputed = pipeline * model * vectors;
		}
	}

	/*
		Atualiza a matriz precomputed_model.
	*/
	void invalidatePreComputedModelMatrix()
	{
		MatrixXf vectors(4, vertices.size() * 3);
		int colv = 0;
		for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			vectors.col(colv++) = it->v0;
			vectors.col(colv++) = it->v1;
			vectors.col(colv++) = it->v2;
		}
		precomputed_model = model * vectors;
	}


	/*
		Método baseado no material fornecido pelo docente.
		Carrega um modelo usando o Assimp.
		file_name contém o nome do arquivo a ser carregado
	*/
	int loadMesh(const std::string &file_name)
	{
		std::ifstream fin(file_name.c_str());
		if (!fin.fail())
			fin.close();
		else
		{
			std::cerr << "Couldn't open file: " << file_name << std::endl;
			return EXIT_FAILURE;
		}

		Assimp::Importer assimp_importer;
		const aiScene* assimp_scene_ = assimp_importer.ReadFile(file_name, aiProcess_Triangulate);

		if (!assimp_scene_)
		{
			std::cerr << assimp_importer.GetErrorString() << std::endl;
			return EXIT_FAILURE;
		}

		if (assimp_scene_->HasMeshes())
		{
			for (unsigned int mesh_id = 0; mesh_id < assimp_scene_->mNumMeshes; mesh_id++)
			{
				const aiMesh *mesh_ptr = assimp_scene_->mMeshes[mesh_id];
				for (unsigned int vertex_id = 0; vertex_id < mesh_ptr->mNumVertices; vertex_id += 3)
				{
					const aiVector3D *vertex_ptr = &mesh_ptr->mVertices[vertex_id];

					// Nesta implementação, estou usando a biblioteca Eigen.

					// glm::dvec3 v0{vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z};
					// glm::dvec3 v1{vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z};
					// glm::dvec3 v2{vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z};
					// ---> Aqui você salva os vértices V0, V1 e V2 do
					// –--> triângulo na sua estrutura de dados!!!

					Vertex ver;
					Vector4f v0(vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z, 1);
					Vector4f v1(vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z, 1);
					Vector4f v2(vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z, 1);
					ver.v0 = v0;
					ver.v1 = v1;
					ver.v2 = v2;
					vertices.push_back(ver);
				}
			}
		}
		return EXIT_SUCCESS;
	}
};