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
}

void World::Init(int height) {


	for (int i = 0; i < 100; i++) {
		p[i].x = std::rand();
		p[i].y = height;

		p[i].vx = 0;
		p[i].vy = -5;
	}
}

void World::Render(Image buff) {
	buff.Fill(Color::BLACK);
	for (int i = 0; i < 100; i++) {
		buff.DrawCircle(p[i].x, p[i].y, p[i].size, Color::WHITE, true);
	}
}

void World::Update(int height) {
	for (int i = 0; i < 100; i++) {
		p[i].Update(height);
	}
}