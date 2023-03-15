#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "framework.h"

#include "entity.h"

void Entity::Render(sUniformData data) {
	data.EntityModelMatrix = this->modelMatrix;
	this->material->Enable(data);
	this->EntityMesh->Render();
	this->material->Disable();
}

void Entity::SetDefaultMatrix(){
	this->modelMatrix.SetIdentity();
}
