
#pragma once

#include "application.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "main/includes.h"
#include "framework.h"
#include "image.h"
#define WORLD_SIZE 200

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
		void Update(int width, int height) {
			this->y += this->vy;

			if (this->y < 0) {
				this->y = height;
				this->x = std::rand() % width;
			}
		}
		void Init(int width, int height) {
			this->x = std::rand() % width;
			this->y = std::rand() % (height*2);

			this->vx = 0;
			this->vy = -3 - (std::rand() % 10);

			this->size = (std::rand()%8) + 2;
		}
};

class World
{
public:
	int size;
	Particle** p;
	Color c;
	World(Color col);
	void Init(int width, int height);
	void Render(Image* buff);
	void Update(int width, int height);
};