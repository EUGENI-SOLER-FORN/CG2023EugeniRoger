#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "entity.h" 
#include "mesh.h"
#include "shader.h" 
#include "texture.h"

struct sLight {
	Vector3 LightPosition;
	Vector3 IntensityDiffuse;
	Vector3 IntensitySpecular;
};

struct sUniformData {
	float ApplyTexture;
	int nLights;
	std::vector<sLight> Lights;
	Matrix44 EntityModelMatrix;
	Matrix44 CameraViewProjection;
	Vector3 EyePosition;
	Vector3 AmbientLight;
};
class Material
{
public:
	Shader* MaterialShader = new Shader();
	Texture* MaterialTexture = new Texture();
	Texture* MaterialNormals = new Texture();
	Vector3 Ambient_K;
	Vector3 Diffuse_K;
	Vector3 Specular_K;
	float Shininess;

	// Constructor
	Material() { }

	// Setters
	void setTexture(Texture* t, Texture* n) { MaterialTexture = t; MaterialNormals = n; }
	void setShininess(float s) { Shininess = s; }
	void setShader(Shader* s) { MaterialShader = s; }
	void setReflections(Vector3 K_a, Vector3 K_d, Vector3 K_s) { Ambient_K = K_a; Diffuse_K = K_d; Specular_K = K_s; }
	
	// Pass to the GPU
	void passTexture(){ this->MaterialShader->SetTexture("u_texture", this->MaterialTexture); this->MaterialShader->SetTexture("u_texture_normals", this->MaterialNormals);}
	void passReflections() { 
		this->MaterialShader->SetVector3("u_K_a", this->Ambient_K);
		this->MaterialShader->SetVector3("u_K_d", this->Diffuse_K);
		this->MaterialShader->SetVector3("u_K_s", this->Specular_K);
	}
	void passShininess(){ 
		this->MaterialShader->SetFloat("u_shine", this->Shininess);
	}
	
	void Enable(const sUniformData& data) {
		this->MaterialShader->Enable(); 
		this->passReflections(); this->passShininess(); this->passTexture(); 
		this->MaterialShader->SetFloat("u_apply_texture", data.ApplyTexture);
		this->MaterialShader->SetMatrix44("u_model", data.EntityModelMatrix);
		this->MaterialShader->SetMatrix44("u_viewprojection", data.CameraViewProjection);
		this->MaterialShader->SetVector3("u_I_a", data.AmbientLight);
		this->MaterialShader->SetVector3("u_I_d", data.Lights[0].IntensityDiffuse);
		this->MaterialShader->SetVector3("u_I_s", data.Lights[0].IntensitySpecular);
		this->MaterialShader->SetVector3("u_light_position", data.Lights[0].LightPosition);
		this->MaterialShader->SetVector3("u_eye_position", data.EyePosition);

	}
	/*
	void passLight(sLight l, int index) {
		char* s;
		sprintf(s, "u_I_d%d", index);
		this->MaterialShader->SetVector3(s, l.IntensityDiffuse);
		sprintf(s, "u_I_s%d", index);
		this->MaterialShader->SetVector3(s, l.IntensitySpecular);
		sprintf(s, "u_light_position%d", index);
		this->MaterialShader->SetVector3(s, l.LightPosition);
	}
	*/

	void Disable() { this->MaterialShader->Disable(); }

	~Material() { delete MaterialShader; delete MaterialTexture; }
};

