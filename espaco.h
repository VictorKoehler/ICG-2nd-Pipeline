#include <eigen-folder/Eigen/Dense> // Númerico
#include <bits/stdc++.h>

#include "objetos.h"
#include "common.h"


using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::VectorXf;
using Eigen::RowVector4f;
using Eigen::Matrix3f;
using Eigen::Matrix4f;
using namespace std;



class Espaco
{
	public: // who cares?

	vector<Objeto> objetos;
	Matrix4f view, projection, viewport, pipeline;



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
		Matrix4f fitScreen = createScaleMatrix(w/2.0, h/2.0, 1);

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
};

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

	Espaco e;
	e.buildCameraByLookAt(pos, lookat, up);

	cout << e.view << endl;
}

/*
	Pequeno teste da matriz Projection, com d = 1;
*/
void example_testProjection()
{
	Espaco e;
	e.buildProjectionMatrix(1);

	cout << e.projection << endl;
}

/*
	Pequeno teste do pipeline, com base no arquivo disponibilizado pelo professor.
*/
Espaco example_testPipeline()
{
	Espaco e;

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