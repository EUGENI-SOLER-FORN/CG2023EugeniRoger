/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "entity.h" 
#include "mesh.h"
#include "shader.h" 

#define EXERCISE_1_TOTAL_TASKS 7

enum eTask {
	Task_a, Task_b, Task_c, Task_d, Task_e, Task_f, Task_extra
};
enum eExer {
	Exercise1, Exercise3, Exercise2, Exercise4
};
class Application
{
public:

	// Window

	SDL_Window* window = nullptr;
	int window_width;
	int window_height;

	float time;
	int pixelRate = 15;
	int radius = 4;
	int flip = 0;
	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame

	int ATTRIBUTE = 0;
	bool MODIFY = false;
	bool OCCLUSION = true;
	bool TEXTURE = true;

	bool MOVING_CAMERA = false;
	std::vector<Entity*> scene;

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;
	FloatImage zBuffer;
	Camera camera;
	Texture Ex2_image;
	Entity* e;
	Shader* exercise1;
	Shader* exercise2;
	Shader* exercise3;
	//Shader* exercise4 = Shader::Get("shaders/exercise1.vs", "shaders/exercise1.fs");
	Shader* shader;

	Mesh* mesh;
	int task = eTask::Task_a;
	int exercise = eExer::Exercise1;
	int exerciseTasks = EXERCISE_1_TOTAL_TASKS;
	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
