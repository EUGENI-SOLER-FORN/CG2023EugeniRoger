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
#include "entity.h"

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	framebuffer->DrawLineBresenham(200, 200, 400, 400, Color::BLACK);
}