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
	//this->DrawCloud(framebuffer, camera, c, vertices);
	this->DrawWireframe(framebuffer, camera, c, vertices);
}

void Entity::DrawWireframe(Image* framebuffer, Camera* camera, const Color& c, std::vector<Vector3> vertices) {
	for (int i = 0; i < vertices.size()-2; i += 3) {
		bool rend0, rend1, rend2;
		// Local to World
		Vector3 worldVertex0 = this->modelMatrix * vertices[i];
		Vector3 worldVertex1 = this->modelMatrix * vertices[i + 1];
		Vector3 worldVertex2 = this->modelMatrix * vertices[i + 2];
		
		// World to Clip
		Vector3 p0 = camera->ProjectVector(worldVertex0, rend0);
		Vector3 p1 = camera->ProjectVector(worldVertex1, rend1);
		Vector3 p2 = camera->ProjectVector(worldVertex2, rend2);

		// Clip to screen
		p0.x = (p0.x + 1) / 2 * framebuffer->width;
		p0.y = (p0.y + 1) / 2 * framebuffer->height;
		p1.x = (p1.x + 1) / 2 * framebuffer->width;
		p1.y = (p1.y + 1) / 2 * framebuffer->height;
		p2.x = (p2.x + 1) / 2 * framebuffer->width;
		p2.y = (p2.y + 1) / 2 * framebuffer->height;

		if (!(rend0 || rend1 || rend2)) {
			framebuffer->DrawLineBresenham(floor(p0.x), floor(p0.y), floor(p1.x), floor(p1.y), c);
			framebuffer->DrawLineBresenham(floor(p1.x), floor(p1.y), floor(p2.x), floor(p2.y), c);
			framebuffer->DrawLineBresenham(floor(p2.x), floor(p2.y), floor(p0.x), floor(p0.y), c);
		}
	}
}

void Entity::DrawCloud(Image* framebuffer, Camera* camera, const Color& c, std::vector<Vector3> vertices) {
	for (int i = 0; i < vertices.size(); i++) {
		bool rend0;
		// Local to World
		Vector3 worldVertex0 = this->modelMatrix * vertices[i];
		// World to Clip
		Vector3 p0 = camera->ProjectVector(worldVertex0, rend0);
		// Clip to Screen
		p0.x = (p0.x + 1) / 2 * framebuffer->width;
		p0.y = (p0.y + 1) / 2 * framebuffer->height;

		if (!rend0) framebuffer->SetPixelSafe(floor(p0.x), floor(p0.y), c);
	}
}

void Entity::SetDefaultMatrix(){
	this->RotationMatrix.SetIdentity();
	this->TranslationMatrix.SetIdentity();
	this->ScaleMatrix.SetIdentity();
	this->modelMatrix.SetIdentity();
}

void Entity::SetModelMatrix(Vector3 translation, Vector3 rotation, Vector3 scale, bool radians) {
	if (!radians) rotation = rotation * DEG2RAD;
	this->Translate(translation.x, translation.y, translation.z);
	this->Rotate(rotation.x, rotation.y, rotation.z);
	this->Scale(scale.x, scale.y, scale.z);
}

void Entity::Rotate(float angleX, float angleY, float angleZ) {
	float cX = cos(angleX);
	float cY = cos(angleY);
	float cZ = cos(angleZ);
	float sX = sin(angleX);
	float sY = sin(angleY);
	float sZ = sin(angleZ);

	RotationMatrix.m[0] = cX*cY;
	RotationMatrix.m[1] = cX*sY*sZ - sX*cZ;
	RotationMatrix.m[2] = cX*sY*cZ - sX*sZ;
	
	RotationMatrix.m[4] = sX*cY;
	RotationMatrix.m[5] = sX*sY*sZ + cX*cZ;
	RotationMatrix.m[6] = sX*sY*cZ - cX*sZ;
	
	RotationMatrix.m[8] = -sY;
	RotationMatrix.m[9] = cY*sZ;
	RotationMatrix.m[10] = cY*cZ;

	this->updateModel();
}

void Entity::Scale(float scaleX, float scaleY, float scaleZ) {
	ScaleMatrix.m[0]  = scaleX;
	ScaleMatrix.m[5]  = scaleY;
	ScaleMatrix.m[10] = scaleZ;
	this->updateModel();
}

void Entity::Translate(float dX, float dY, float dZ) {
	this->modelMatrix.TranslateLocal(dX, dY, dZ);
}