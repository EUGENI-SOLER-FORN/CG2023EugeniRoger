#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h" 

#define NEAR 1
#define FAR 2
#define FOV 3
#define ZOOM 4

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);
	this->camera = Camera();
	
	Vector3 eye = Vector3(0, 0, -50);
	Vector3 center= Vector3(0, 0, 0);
	Vector3 up = Vector3(0, 1, 0);
	this->camera.LookAt(eye, center, up);
	
	this->camera.SetPerspective(60 * DEG2RAD, 0.5, 0.01, 100);

	Mesh* m = new Mesh();
	m->LoadOBJ("meshes/lee.obj");
	scene.push_back(new Entity(m, Color::RED));
	scene.push_back(new Entity(m, Color::GREEN));
	scene.push_back(new Entity(m, Color::BLUE));
	this->MODIFY = ZOOM;
}

Application::~Application()
{
	SDL_DestroyWindow(window);
}

void Application::Init(void)
{

	Vector3 trans = Vector3(40, 0, 70);
	Vector3 rot = Vector3(0, 0, 30 * DEG2RAD);
	Vector3 scale = Vector3(30);
	scene[0]->SetModelMatrix(trans, rot, scale);

	trans = Vector3(0, 0, 30);
	rot = Vector3(0, 0, 30 * DEG2RAD);
	scale = Vector3(50);
	scene[1]->SetModelMatrix(trans, rot, scale);

	trans = Vector3(0, 0, 50);
	rot = Vector3(0);
	scale = Vector3(50);
	scene[2]->SetModelMatrix(trans, rot, scale);

	std::cout << "Initiating..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	// ...
	framebuffer.Fill(Color::BLACK);

	scene[0]->Render(&framebuffer, &camera, scene[0]->entityColor);
	scene[1]->Render(&framebuffer, &camera, scene[1]->entityColor);
	scene[2]->Render(&framebuffer, &camera, scene[2]->entityColor);

	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	float c = cos(time);
	
	scene[0]->Rotate(time, 0, 0);
	scene[1]->Scale(50 * (c*c + 0.5), 50, 50);
	scene[2]->Translate((std::rand()%3-1)/20.0, (std::rand() % 3 - 1) / 20.0, 0);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	Vector3 direction = this->camera.eye - this->camera.center;
	Vector3 new_direction = Vector3(0);
	float distance = direction.Length();
	float alpha = 10 * DEG2RAD;

	// KEY CODES : https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
		// Change perspective mode
		case SDLK_p: this->camera.SetPerspective(4*alpha, 0.5, this->camera.near_plane, this->camera.near_plane); break;
		case SDLK_o: this->camera.SetOrthographic(-100, 100, 100, -100, this->camera.near_plane, this->camera.near_plane); break;
		
		// Zoom in/out
		case SDLK_PAGEUP: 
			switch (MODIFY) {
				case ZOOM:
					this->camera.eye = this->camera.eye - direction * 0.1;
					break;
				case NEAR:
					if(this->camera.far_plane > this->camera.near_plane + 1) this->camera.near_plane++;
					break;
				case FAR:
					this->camera.far_plane++;
					break;
				case FOV:
					this->camera.fov += alpha;
					if(this->camera.fov > PI) this->camera.fov = PI;
					break;
				default:break;
			}
			this->camera.UpdateProjectionMatrix();
			this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
			break;
		case SDLK_PAGEDOWN:
			switch (MODIFY) {
			case ZOOM:
				this->camera.eye = this->camera.eye + direction * 0.1;
				break;
			case NEAR:
				this->camera.near_plane--;
				break;
			case FAR:
				if (this->camera.far_plane-1 > this->camera.near_plane) this->camera.far_plane--;
				break;
			case FOV:
				this->camera.fov -= alpha;
				if (0 >= this->camera.fov) this->camera.fov = alpha;
				break;
			default:break;
			}
			this->camera.UpdateProjectionMatrix();
			this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
			break;

		// Move center position
		case SDLK_LEFT:
			this->camera.center.x--;
			this->camera.eye.x--;
			this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
			break; 
		case SDLK_RIGHT: 
			this->camera.center.x++;
			this->camera.eye.x++;
			this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
			break; 
		case SDLK_UP:
			this->camera.center.y++;
			this->camera.eye.y++;
			this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
			break;
		case SDLK_DOWN:
			this->camera.center.y--;
			this->camera.eye.y--;
			this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
			break;
		
		case SDLK_n:
			MODIFY = NEAR; 
			break;
		case SDLK_f:
			MODIFY = FAR;
			break;
		case SDLK_v:
			MODIFY = FOV;
			break;
		case SDLK_z:
			MODIFY = ZOOM;
			break;

	}
	std::cout << camera.near_plane << std::endl;
	std::cout << camera.far_plane << std::endl;
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		MOVING_CAMERA = true;
	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		MOVING_CAMERA = false;
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (MOVING_CAMERA) {
		Vector3 direction = this->camera.eye - this->camera.center;
		Vector3 rotateX = Vector3(0);
		Vector3 rotateY = Vector3(0);

		float alphaX = mouse_delta.x * DEG2RAD;
		float alphaY = mouse_delta.y * DEG2RAD;

		rotateX.x = direction.x * cos(alphaX) + direction.z * sin(alphaX);
		rotateX.y = direction.y;
		rotateX.z = -direction.x * sin(alphaX) + direction.z * cos(alphaX);

		rotateY.x = rotateX.x;
		rotateY.y = rotateX.y * cos(alphaY) - rotateX.z * sin(alphaY);
		rotateY.z = rotateX.y * sin(alphaY) + rotateX.z * cos(alphaY);

		this->camera.eye = this->camera.center + rotateY;
		camera.LookAt(camera.eye, camera.center, camera.up);
	}
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}