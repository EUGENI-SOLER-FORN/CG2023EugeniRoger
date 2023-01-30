#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"

class Entity
{
public:
	Mesh* entityMesh;
	Matrix44 modelMatrix;

	Entity(Mesh* eM, Matrix44 mM) {
		entityMesh = eM;
		modelMatrix = mM;
	}
	Entity(Mesh* eM) {
		entityMesh = eM;
	}
	Entity(){}
	~Entity() { delete entityMesh; }

	void setMesh(Mesh* m) { entityMesh = m; }
	void Render(Image* framebuffer, Camera* camera, const Color& c);
private:

};