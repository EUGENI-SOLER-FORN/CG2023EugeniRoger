#include "application.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "main/includes.h"
#include "framework.h"
#include "image.h"

Particles::Particles(Color col) {
	c = col;
}

void Particles::Init() {
	for (int i = 0; i < 100; i++) {
		p[i].x = std::rand();
		p[i].y = std::rand();

		p[i].vx = 0;
		p[i].vy = -1;
	}
}

void Particles::Render(Image buff) {
	buff.Fill(Color::BLACK);
	for (int i = 0; i < 100; i++) {
		buff.DrawCircle(p[i].x, p[i].y, p[i].size, c, true);
	}
}

void Particles::Update() {
	for (int i = 0; i < 100; i++) {
		p[i].x += p[i].vx;
		p[i].y += p[i].vy;

		if (p[i].y < 0) {
			p[i].y = std::rand();
			do {
				p[i].vy = -std::rand();
			} while (p[i].vy < -50);
		}
	}
}