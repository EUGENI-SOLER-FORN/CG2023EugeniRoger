
#pragma once

#include "application.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "main/includes.h"
#include "framework.h"
#include "image.h"

class Particle {
	public:
		int x;
		int y;
		float vx;
		float vy;
		int size;
		Particle() {
			x = 0;
			y = 0;
			vx = 0;
			vy = 0;
			size = 1;
		}
		void Update(int height) {
			this->y += this->vy;

			if (this->y < 0) {
				this->y = height;
			}
		}
};

class World
{
public:
	Particle p[100];
	Color c;
	World(Color col);
	void Init(int height);
	void Render(Image buff);
	void Update(int height);
};