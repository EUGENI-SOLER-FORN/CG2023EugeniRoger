#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "entity.h" 
#include "mesh.h"
#include "shader.h" 

class Light
{
public:

	Vector3 LightPosition;
	Vector3 IntensityDiffuse;
	Vector3 IntensitySpecular;
};
