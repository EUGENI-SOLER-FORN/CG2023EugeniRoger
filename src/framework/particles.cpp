#include "application.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "particles.h"

World::World(Color col) {
	c = col;
	p = new Particle* [WORLD_SIZE];
}

void World::Init(int width, int height) {
	for (int i = 0; i < WORLD_SIZE; i++) {
		p[i] = new Particle();
		p[i]->Init(width, height);
	}
}

void World::Render(Image* buff) {
	buff->Fill(Color::BLACK);
	for (int i = 0; i < WORLD_SIZE; i++) {
		buff->DrawCircle(p[i]->x, p[i]->y, p[i]->size, this->c, true);
	}
}

void World::Update(int width, int height) {
	for (int i = 0; i < WORLD_SIZE; i++) {
		p[i]->Update(width, height);
	}
}