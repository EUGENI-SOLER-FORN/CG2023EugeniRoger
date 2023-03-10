#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "entity.h" 
#include "mesh.h"
#include "shader.h" 
#include "texture.h"

class Material
{
public:
	Shader* MaterialShader;
	Texture* MaterialTexture;
	Vector3 Ambient_K;
	Vector3 Diffuse_K;
	Vector3 Specular_K;
	Vector3 Shininess;

	void setTexture(Texture* t) { MaterialTexture = t; }
	void setShader(Shader* s) { MaterialShader = s; }
	void setReflections(Vector3 K_a, Vector3 K_d, Vector3 K_s) { Ambient_K = K_a; Diffuse_K = K_d; Specular_K = K_s; }
	Material() { }
	~Material() { delete MaterialShader; delete MaterialTexture; }


};