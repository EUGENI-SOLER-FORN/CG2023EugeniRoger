#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "texture.h"
#include "framework.h"
#include "material.h"

class Entity
{
public:
	int MeshCount = 0;
	Mesh* EntityMesh;
	Material* material;
	Matrix44 modelMatrix;

	Entity(){
		this->SetDefaultMatrix();
	}
	~Entity() { delete material; delete EntityMesh; }

	void setMesh(Mesh* m) { EntityMesh = m; }
	void Render();
	void SetDefaultMatrix();

private:
};