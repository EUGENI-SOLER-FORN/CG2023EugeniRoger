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

void Entity::Render() {
	this->entityMesh->Render();
}

void Entity::SetDefaultMatrix(){
	this->modelMatrix.SetIdentity();
}
