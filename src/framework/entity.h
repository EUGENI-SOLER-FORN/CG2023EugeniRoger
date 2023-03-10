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

class Entity
{
public:
	Mesh* entityMesh;
	Color entityColor;
	Texture* texture_shader;
	Matrix44 modelMatrix;

	Entity(Mesh* eM, Matrix44 mM, Color c) {
		this->entityMesh = eM;
		this->entityColor = c;
		this->modelMatrix = mM;
		texture_shader = new Texture();
	}
	Entity(Mesh* eM, Color c) {
		this->entityColor = c;
		this->entityMesh = eM;
		this->SetDefaultMatrix();
		texture_shader = new Texture();
	}
	Entity(Color c){
		this->entityColor = c;
		this->SetDefaultMatrix();
		texture_shader = new Texture();
	}
	Entity(){
		this->SetDefaultMatrix();
		texture_shader = new Texture();
	}
	~Entity() { delete entityMesh; delete texture_shader; }

	void setMesh(Mesh* m) { entityMesh = m; }
	void setTexture(Texture* m) { texture_shader = m; }
	void Render();
	void SetDefaultMatrix();

private:
};