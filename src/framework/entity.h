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


class Entity
{
public:
	Mesh* entityMesh;
	Matrix44 modelMatrix;
	Color entityColor;

	Entity(Mesh* eM, Matrix44 mM, Color c) {
		this->entityMesh = eM;
		this->entityColor = c;
		this->modelMatrix = mM;
	}
	Entity(Mesh* eM, Color c) {
		this->entityColor = c;
		this->entityMesh = eM;
		this->SetDefaultMatrix();
	}
	Entity(Color c){
		this->entityColor = c;
		this->SetDefaultMatrix();
	}
	~Entity() { delete entityMesh; }

	void setMesh(Mesh* m) { entityMesh = m; }
	void Render(Image* framebuffer, Camera* camera, const Color& c);

	void SetDefaultMatrix();
	void SetModelMatrix(Vector3 translation, Vector3 rotation, Vector3 scale, bool radians = true);
	void DrawCloud(Image* framebuffer, Camera* camera, const Color&, std::vector<Vector3> vertices);
	void DrawMesh(Image* framebuffer, Camera* camera, const Color& c, std::vector<Vector3> vertices);
private:
};