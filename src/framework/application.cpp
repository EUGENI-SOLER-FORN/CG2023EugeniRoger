#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h" 

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

	this->framebuffer.Resize(w, h);
	this->zBuffer.Resize(w, h);
	this->camera = Camera();
	this->shader = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs");

	this->ATTRIBUTE = FOV;
	this->MODIFY = ORBIT;
}

Application::~Application()
{
}

void Application::Init(void)
{
	this->mesh = new Mesh();
	this->mesh->CreateQuad();
	std::cout << "Initiating..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	// ...
	//glEnable(GL_DEPTH_TEST);
	this->shader->Enable();
	this->shader->SetFloat("u_task", task);
	this->shader->SetVector3("u_dimensions", Vector3(this->window_width, this->window_height, 0));

	this->mesh->Render();
	this->shader->Disable();
}

// Called after render
void Application::Update(float seconds_elapsed)
{

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
		case SDLK_LEFT:
			this->camera.center.x++;
			this->camera.eye.x++;
			break; 
		case SDLK_RIGHT: 
			this->camera.center.x--;
			this->camera.eye.x--;
			break; 
		case SDLK_UP:
			this->camera.center.y++;
			this->camera.eye.y++;
			break;
		case SDLK_DOWN:
			this->camera.center.y--;
			this->camera.eye.y--;
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

		// Change Modes
		case SDLK_c:
			scene[1]->MODE = (scene[1]->MODE == eRenderMode::TRIANGLES) ? eRenderMode::WIREFRAME : eRenderMode::TRIANGLES;
			break;
		case SDLK_w:
			scene[1]->MODE = (scene[1]->MODE == eRenderMode::WIREFRAME) ? eRenderMode::POINTCLOUD : eRenderMode::WIREFRAME;
			break;
		case SDLK_z: OCCLUSION =! OCCLUSION;	break;
		case SDLK_t: TEXTURE = !TEXTURE;	break;
		
		// Change between tasks
		case SDLK_PERIOD: task = (task + 1) % 7; break;
		case SDLK_COMMA: task = (task + 6) % 7; break;

		// Change between exercises (shaders)
		case SDLK_1: this->shader = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs"); break;
		case SDLK_2: this->shader = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs"); break;
		case SDLK_3: this->shader = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs"); break;
		case SDLK_4: this->shader = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs"); break;

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
		}
		else if (MODIFY == CENTER) {
			Vector3 movement = Vector3(mouse_delta.x, mouse_delta.y, 0);

			this->camera.center = this->camera.center + movement;
		}
		camera.LookAt(camera.eye, camera.center, camera.up);
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	Vector3 direction = this->camera.eye - this->camera.center;
	if (dy > 0) this->camera.eye = this->camera.eye - direction * 0.1;
	else this->camera.eye = this->camera.eye + direction * 0.1;
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}