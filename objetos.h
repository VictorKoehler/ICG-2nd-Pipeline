#include <assimp/Importer.hpp> 	   // C++ importer interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>


using Eigen::Vector4f;
using Eigen::Matrix4f;
using namespace std;

typedef struct
{
	Vector4f v0, v1, v2;
}Vertice;

class Objeto
{
	public:
	Objeto()
	{
		model.setIdentity();
	}
	Objeto(const std::string &file_name)
	{
		model.setIdentity();
		loadMesh(file_name);
	}

	vector<Vertice> vertices;
	Matrix4f model;

	// file_name contém o nome do arquivo a ser carregado
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
					// glm::dvec3 v0{vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z};
					// glm::dvec3 v1{vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z};
					// glm::dvec3 v2{vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z};
					// ---> Aqui você salva os vértices V0, V1 e V2 do
					// –--> triângulo na sua estrutura de dados!!!

					Vertice ver;
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