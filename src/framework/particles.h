#include "application.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include "main/includes.h"
#include "framework.h"
#include "image.h"

class Particles {
	typedef struct {
		int x;
		int y;
		float vx;
		float vy;
		int size;
	}Particle;
public:
	Particle p[100];
	Color c;
	Particles(Color col);
	void Init();
	void Render(Image buff);
	void Update();
};
