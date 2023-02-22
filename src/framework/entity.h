#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "framework.h"

typedef struct sTriangleInfo {
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	Vector2 uv0;
	Vector2 uv1;
	Vector2 uv2;
	Color c0;
	Color c1;
	Color c2;
	Image* texture;
}sTriangleInfo;

enum class eRenderMode {
	POINTCLOUD,
	WIREFRAME,
	TRIANGLES,
	TRIANGLES_INTERPOLATED,
	TEXTURE
};

class Entity
{
public:
	
	eRenderMode MODE = eRenderMode::TRIANGLES_INTERPOLATED;
	Mesh* entityMesh;
	Matrix44 RotationMatrix;
	Matrix44 ScaleMatrix;
	Matrix44 TranslationMatrix;
	Matrix44 modelMatrix;
	Color entityColor;
	Image* texture;

	Entity(Mesh* eM, Matrix44 mM, Color c) {
		this->entityMesh = eM;
		this->entityColor = c;
		this->modelMatrix = mM;
		texture = new Image();
	}
	Entity(Mesh* eM, Color c) {
		this->entityColor = c;
		this->entityMesh = eM;
		this->SetDefaultMatrix();
		texture = new Image();
	}
	Entity(Color c){
		this->entityColor = c;
		this->SetDefaultMatrix();
		texture = new Image();
	}
	~Entity() { delete entityMesh; }

	void setMesh(Mesh* m) { entityMesh = m; }
	void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer);

	void SetDefaultMatrix();
	void SetModelMatrix(Vector3 translation, Vector3 rotation, Vector3 scale, bool radians = true);
	void updateModel() { this->modelMatrix = this->TranslationMatrix * this->ScaleMatrix * this->RotationMatrix; }

	void Rotate(float angleX, float angleY, float angleZ);
	void Translate(float dX, float dY, float dZ);
	void Scale(float scaleX, float scaley, float scaleZ);
	
	void DrawCloud(Image* framebuffer, Camera* camera, FloatImage* zBuffer, std::vector<Vector3> vertices);
	void DrawWireframe(Image* framebuffer, Camera* camera, FloatImage* zBuffer, std::vector<Vector3> vertices);
	void DrawEntityTriangles(Image* framebuffer, Camera* camera, FloatImage* zBuffer, std::vector<Vector3> vertices);
	void DrawEntityTrianglesInterpolated(Image* framebuffer, Camera* camera, FloatImage* zBuffer, std::vector<Vector3> vertices, bool oclusions=true);


	void Update(float seconds_elapsed);
private:
};