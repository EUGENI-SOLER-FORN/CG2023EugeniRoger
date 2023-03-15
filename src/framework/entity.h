#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "light.h" 
#include "material.h" 
#include "mesh.h"
#include "texture.h"
#include "framework.h"

class Entity
{
public:
	Mesh* EntityMesh;
	Material* material;
	Matrix44 modelMatrix;

	Entity(){
		this->SetDefaultMatrix();
	}
	~Entity() { delete material; delete EntityMesh; }

	void setMesh(Mesh* m) { EntityMesh = m; }
	void Render(sUniformData uniformData);
	void SetDefaultMatrix();

private:
};