#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h" 
#define EXERCISE_1_TOTAL_TASKS 7
#define EXERCISE_2_TOTAL_TASKS 6
#define EXERCISE_3_TOTAL_TASKS 3
#define EXERCISE_4_TOTAL_TASKS 1
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
	Vector3 up = Vector3(0, 1, 0);
	Vector3 eye = Vector3(0, 0, 1);
	Vector3 center = Vector3(0, 0, 0);
	this->camera.LookAt(eye, center, up);
	this->camera.SetPerspective(45, (float)window_width/window_height, 0.01, 100);
	exercise1 = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs");
	exercise2 = Shader::Get("shaders/exercise2.vs", "shaders/exercise2.fs");
	exercise3 = Shader::Get("shaders/exercise3.vs", "shaders/exercise3.fs");
	exercise4 = Shader::Get("shaders/raster.vs", "shaders/raster.fs");
	Ex2_image.Load("images/fruits.png", false);

	this->shader = exercise1;
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

	Mesh* m = new Mesh();
	m->LoadOBJ("meshes/lee.obj");
	scene.push_back(new Entity(m, Color::RED));
	scene[0]->modelMatrix.SetTranslation(0, -0.25, 0);
	scene[0]->texture_shader->Load("textures/lee_color_specular.tga", false);
	std::cout << "Initiating..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	switch (exercise) {
		case eExer::Exercise1: this->shader = this->exercise1; break;
		case eExer::Exercise2: this->shader = this->exercise2; break;
		case eExer::Exercise3: this->shader = this->exercise3; break;
		case eExer::Exercise4: this->shader = this->exercise4; break;
	}
	// ...
	this->shader->Enable();
	if(this->exercise == eExer::Exercise4) glEnable(GL_DEPTH_TEST);
	this->shader->SetFloat("u_task", task);
	this->shader->SetFloat("u_width",  this->window_width);
	this->shader->SetFloat("u_height", this->window_height);
	this->shader->SetFloat("u_time", time);
	this->shader->SetFloat("u_pixelRate", pixelRate);
	this->shader->SetFloat("u_radius", radius);
	this->shader->SetFloat("u_flip", flip);
	
	this->shader->SetTexture("u_image", &Ex2_image);
	this->shader->SetTexture("u_texture", scene[0]->texture_shader);

	this->shader->SetMatrix44("u_model", this->scene[0]->modelMatrix);
	this->shader->SetMatrix44("u_viewprojection", this->camera.viewprojection_matrix);

	if (this->exercise == eExer::Exercise4) scene[0]->Render();
	else this->mesh->Render();

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
		case SDLK_PERIOD: task = (task + 1) % exerciseTasks; break;
		case SDLK_COMMA: task = (task + exerciseTasks - 1) % exerciseTasks; break;
		case SDLK_PLUS:  pixelRate = (pixelRate + 1) % 50;  radius = (radius + 1) % 20;  flip = (flip + 1) % 3; break;
		case SDLK_MINUS: pixelRate = (pixelRate + 49) % 50; radius = (radius + 19) % 20; flip = (flip + 2) % 3; break;

		// Change between exercises (shaders)
		case SDLK_1: exercise = eExer::Exercise1; exerciseTasks = EXERCISE_1_TOTAL_TASKS; task = eTask::Task_a; break;
		case SDLK_2: exercise = eExer::Exercise2; exerciseTasks = EXERCISE_2_TOTAL_TASKS; task = eTask::Task_a; break;
		case SDLK_3: exercise = eExer::Exercise3; exerciseTasks = EXERCISE_3_TOTAL_TASKS; task = eTask::Task_a; break;
		case SDLK_4: exercise = eExer::Exercise4; exerciseTasks = EXERCISE_4_TOTAL_TASKS; task = eTask::Task_a; break;

	}
	this->camera.SetAspectRatio((float)window_width / window_height);
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