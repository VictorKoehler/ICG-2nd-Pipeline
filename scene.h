#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

#include "objectmodel.h"
#include "common.h"


using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::VectorXf;
using Eigen::RowVector4f;
using Eigen::Matrix3f;
using Eigen::Matrix4f;
using namespace std;



class Scene
{
	public: // who cares?
	/*
		Construtor padrão.
	*/
	Scene()
	{
		view = Matrix4f::Identity();
		projection = Matrix4f::Identity();
		viewport = Matrix4f::Identity();
		pipeline = Matrix4f::Identity();
	}

	Scene(Vector3f camera_position, Vector3f camera_lookAt, Vector3f camera_up,
		float camera_dist, int screen_width, int screen_height)
	{
		buildCameraByLookAt(camera_position, camera_lookAt, camera_up);
		buildProjectionMatrix(camera_dist);
		buildViewportMatrix(screen_width, screen_height);
		buildPipeline();
	}

	vector<ObjectModel> objects;
	Matrix4f view, projection, viewport, pipeline;



	/*
		Carrega um objeto no espaço.
	*/
	int loadObject(const std::string &file_name)
	{
        ObjectModel o;
        int r = o.loadMesh(file_name);
        if (r == EXIT_SUCCESS)
        {
            objects.push_back(o);
        }
		return r;
	}

	/*
		Posiciona a câmera apontada com a direção indicada.
	*/
	void buildCameraByDirection(Vector3f position, Vector3f direction, Vector3f up)
	{
		Vector3f camera_z = direction.normalized() * (-1);
		Vector3f camera_x = up.cross(camera_z).normalized();
		Vector3f camera_y = camera_z.cross(camera_x).normalized();

		Matrix4f Bt = createTransposedBasis(camera_x, camera_y, camera_z);
		Matrix4f t = createTranslationMatrix_3dv((-1)*position);

		view = Bt * t;
	}

	/* 
		Posiciona a câmera apontada para a posição indicada em lookAt.
		Este método simplesmente chama setCameraByDirection com lookAt recalculado.
	*/
	void buildCameraByLookAt(Vector3f position, Vector3f lookAt, Vector3f up)
	{
		buildCameraByDirection(position, lookAt - position, up);
	}


	/*
		Redefine a matriz de projeção.
	*/
	void buildProjectionMatrix(float d)
	{
		// projection = (Matrix4f() << Matrix3f::Identity(),
		// 			 (Vector3f() << 0, 0, d).finished(),
		// 			 (RowVector4f() << 0, 0, (-1/d), 0).finished() ).finished();
		projection.setIdentity();
		projection(2, 3) = d;
		projection(3, 2) = -1.0/d;
		projection(3, 3) = 0;
	}


	/*
		Redefine a matriz Viewport.
	*/
	void buildViewportMatrix(int width, int height)
	{
		float w = (float)(width - 1), h = (float)(height - 1);

		Matrix4f invertY = createScaleMatrix(1, -1, 1);
		Matrix4f translateToOrigin = createTranslationMatrix(1, 1, 0);
		Matrix4f fitScreen = createScaleMatrix((w-1)/2.0, (h-1)/2.0, 1);

		//cout << invertY << endl << endl << translateToOrigin << endl << endl << fitScreen << endl << endl;

		viewport = fitScreen * translateToOrigin * invertY;
	}


	/*
		Atualiza a matriz do pipeline.
	*/
	void buildPipeline()
	{
		pipeline = viewport * projection * view;
	}


	void invalidateAllObjects()
	{
		for (vector<ObjectModel>::iterator it = objects.begin(); it != objects.end(); it++)
		{
			it->invalidatePreComputedMatrix(pipeline, true);
		}
	}
};
