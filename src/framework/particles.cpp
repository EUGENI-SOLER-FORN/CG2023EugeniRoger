#include "application.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "particles.h"

Particles::Particles(Color col) {
	c = col;
}

void Particles::Init(int height) {


	for (int i = 0; i < 100; i++) {
		p[i].x = std::rand();
		p[i].y = height;

		p[i].vx = 0;
		p[i].vy = -5;
	}
}

void Particles::Render(Image buff) {
	buff.Fill(Color::BLACK);
	for (int i = 0; i < 100; i++) {
		buff.DrawCircle(p[i].x, p[i].y, p[i].size, Color::WHITE, true);
	}
}

void Particles::Update(int height) {
	for (int i = 0; i < 100; i++) {
		//p[i].x += p[i].vx;
		p[i].y += p[i].vy;

		if (p[i].y < 0) {
			p[i].y = height;
			
		}
	}
}