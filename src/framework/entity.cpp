#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "framework.h"

#include "entity.h"

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	std::vector<Vector3> vertices = this->entityMesh->GetVertices();
	this->DrawCloud(framebuffer, camera, c, vertices);
	//this->DrawMesh(framebuffer, camera, c, vertices);
}

void Entity::DrawMesh(Image* framebuffer, Camera* camera, const Color& c, std::vector<Vector3> vertices) {
	bool rend0, rend1, rend2;
	for (int i = 0; i < vertices.size(); i++) {
		Vector3 worldVertex0 = this->modelMatrix * vertices[i];
		Vector3 worldVertex1 = this->modelMatrix * vertices[i + 1];
		Vector3 worldVertex2 = this->modelMatrix * vertices[i + 2];
		
		Vector3 p0 = camera->ProjectVector(worldVertex0, rend0);
		Vector3 p1 = camera->ProjectVector(worldVertex1, rend1);
		Vector3 p2 = camera->ProjectVector(worldVertex2, rend2);

		if (!(rend0 && rend1)) framebuffer->DrawLineBresenham(floor(p0.x), floor(p0.y), floor(p1.x), floor(p1.y), c);
		if (!(rend1 && rend2)) framebuffer->DrawLineBresenham(floor(p1.x), floor(p1.y), floor(p2.x), floor(p2.y), c);
		if (!(rend2 && rend0)) framebuffer->DrawLineBresenham(floor(p2.x), floor(p2.y), floor(p0.x), floor(p0.y), c);

		framebuffer->SetPixelSafe(worldVertex0.x, worldVertex0.y, c);
		framebuffer->SetPixelSafe(p0.x, p0.y, Color::BLUE);
		//std::cout << p0.x << " " << p0.y << std::endl;
	}
}

void Entity::DrawCloud(Image* framebuffer, Camera* camera, const Color& c, std::vector<Vector3> vertices) {
	bool rend0;
	for (int i = 0; i < vertices.size(); i++) {
		Vector3 worldVertex0 = this->modelMatrix * vertices[i];
		Vector3 p0 = camera->ProjectVector(worldVertex0, rend0);

		framebuffer->SetPixelSafe(worldVertex0.x, worldVertex0.y, c);
		framebuffer->SetPixelSafe(p0.x, p0.y, Color::BLUE);
	}
}

void Entity::SetDefaultMatrix(){
	Matrix44 Model = Matrix44();
}

void Entity::SetModelMatrix(Vector3 translation, Vector3 rotation, Vector3 scale, bool radians) {
	Matrix44 TranslationMatrix = Matrix44();
	Matrix44 RotationMatrix = Matrix44();
	Matrix44 ScaleMatrix = Matrix44();
	
	TranslationMatrix.SetTranslation(translation.x, translation.y, translation.z);
	
	if (!radians) rotation = rotation * DEG2RAD;
		
	RotationMatrix.SetRotation(rotation.x, rotation);
	
	ScaleMatrix.SetIdentity();
	ScaleMatrix.m[0] = scale.x;
	ScaleMatrix.m[5] = scale.y;
	ScaleMatrix.m[10] = scale.z;

	this->modelMatrix = ScaleMatrix * RotationMatrix * TranslationMatrix;
}