#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h" 
#include "material.h" 
#define ENTITIES 3
#define NEAR 1
#define FAR 2
#define FOV 3

#define ORBIT false
#define CENTER true

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
	
	// Camera settings
	this->camera = Camera();
	Vector3 up = Vector3(0, 1, 0);
	Vector3 eye = Vector3(0, 0, 1);
	Vector3 center = Vector3(0, 0, 0);
	this->camera.LookAt(eye, center, up);
	this->camera.SetPerspective(45, (float)window_width/window_height, 0.0001, 100);
	
	// Light settings
	this->IntensityAmbient = Vector3(20/255.0, 20/255.0, 30/255.0);
	sLight light0;
	light0.IntensityDiffuse = Vector3(1);
	light0.IntensitySpecular = Vector3(1);
	light0.LightPosition = Vector3(2, 2, 3);
	this->lights.push_back(light0);

	this->ATTRIBUTE = FOV;
	this->MODIFY = ORBIT;
}

Application::~Application()
{
}

void Application::Init(void)
{
	Mesh* lee = new Mesh();
	lee->LoadOBJ("meshes/lee.obj");
	Texture* leeT = new Texture();
	leeT->Load("textures/lee_color_specular.tga", false);
	Texture* leeN = new Texture();
	leeN->Load("textures/lee_normal.tga", false);

	scene.push_back(new Entity());

	scene[0]->modelMatrix.SetTranslation(0, -0.25, 0.5);
	scene[0]->setMesh(lee);

	Phong = Shader::Get("shaders/phong.vs", "shaders/phong.fs");
	Gouraud = Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs");
	EntityMaterial = new Material();

	EntityMaterial->setShader(Gouraud);
	EntityMaterial->setTexture(leeT, leeN);
	EntityMaterial->setReflections(Vector3(1), Vector3(200/255.0), Vector3(1));
	EntityMaterial->setShininess(10);
	
	scene[0]->material = EntityMaterial;

	std::cout << "Initiating..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	// ...
	glEnable(GL_DEPTH_TEST);

	data.AmbientLight = this->IntensityAmbient;
	data.CameraViewProjection = this->camera.GetViewProjectionMatrix();
	data.EyePosition = this->camera.eye;
	data.nLights = 1;
	data.Lights = this->lights;
	data.ApplyTexture = APPLY_TEXTURE;
	scene[0]->Render(data);

}

// Called after render
void Application::Update(float seconds_elapsed)
{
	this->camera.SetAspectRatio((float)window_width / window_height);
	this->camera.UpdateProjectionMatrix();
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
		case SDLK_p: this->camera.SetPerspective(4 * alpha, (float)this->window_width/this->window_height, this->camera.near_plane, this->camera.far_plane); break;
		case SDLK_o: this->camera.SetOrthographic(-1, 1, 1, -1, this->camera.near_plane, this->camera.far_plane); break;
		
		// Zoom in/out
		case SDLK_PAGEUP: 
			switch (ATTRIBUTE) {
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
			break;

		case SDLK_PAGEDOWN:
			switch (ATTRIBUTE) {
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
			break;

		// Move center and eye position
		case SDLK_RIGHT: 
			this->camera.center.x+= 0.1;
			this->camera.eye.x+= 0.1 ;
			break; 
		case SDLK_LEFT:
			this->camera.center.x-= 0.1;
			this->camera.eye.x-= 0.1;
			break; 
		case SDLK_UP:
			this->camera.center.y+= 0.1;
			this->camera.eye.y+= 0.1;
			break;
		case SDLK_DOWN:
			this->camera.center.y-= 0.1;
			this->camera.eye.y-= 0.1;
			break;
		
		// Change Attributes
		case SDLK_n:
			ATTRIBUTE = NEAR;
			break;
		case SDLK_f:
			ATTRIBUTE = FAR;
			break;
		case SDLK_v:
			ATTRIBUTE = FOV;
			break;

		// Modify Parameters
		case SDLK_m:
			MODIFY = CENTER;
			break;
		case SDLK_r:
			MODIFY = ORBIT;
			break;

		case SDLK_g:
			EntityMaterial->setShader(Gouraud);
			std::cout << "GOURAUD" << std::endl;
			break;
		case SDLK_h:
			EntityMaterial->setShader(Phong);
			std::cout << "PHONG" << std::endl;
			break;
		case SDLK_t:
			APPLY_TEXTURE = APPLY_TEXTURE % 2 == 0 ? 1 : 0;
			break;
		// Change between tasks
		/*
		case SDLK_PERIOD: entityNumber = (entityNumber + 1) % ENTITIES; break;
		case SDLK_COMMA: entityNumber = (entityNumber + ENTITIES - 1) % ENTITIES;  break;
		*/
	}
	this->camera.UpdateProjectionMatrix();
	this->camera.LookAt(this->camera.eye, this->camera.center, this->camera.up);
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
		if (MODIFY == ORBIT) {
			std::cout << std::endl;

			Vector3 direction = this->camera.eye - this->camera.center;
			Vector3 rotateX = Vector3(0);
			Vector3 rotateY = Vector3(0);

			float alphaX = mouse_delta.x/2 * DEG2RAD;
			float alphaY = mouse_delta.y/2 * DEG2RAD;

			rotateX.x = direction.x * cos(alphaX) + direction.z * sin(alphaX);
			rotateX.y = direction.y;
			rotateX.z = -direction.x * sin(alphaX) + direction.z * cos(alphaX);

			rotateY.x = rotateX.x;
			rotateY.y = rotateX.y * cos(alphaY) - rotateX.z * sin(alphaY);
			rotateY.z = rotateX.y * sin(alphaY) + rotateX.z * cos(alphaY);

			this->camera.eye = this->camera.center + rotateY;
		}
		else if (MODIFY == CENTER) {
			Vector3 movement = Vector3(mouse_delta.x/2, mouse_delta.y/2, 0);
			this->camera.center = this->camera.center + movement;
		}
		camera.LookAt(camera.eye, camera.center, camera.up);
		this->camera.UpdateProjectionMatrix();
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	Vector3 direction = this->camera.eye - this->camera.center;
	if (dy > 0) {
		this->camera.eye = this->camera.eye - direction * 0.1;
	}
	else {
		this->camera.eye = this->camera.eye + direction * 0.1;
	}
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}