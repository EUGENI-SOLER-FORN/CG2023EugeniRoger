#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

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

	this->LastClick = Vector2(mouse_position.x, mouse_position.y);
	this->global_col = Color::BLACK;
	this->framebuffer.Fill(Color::WHITE);
	this->DRAWING = false;
	this->MODE = FREEHAND;
}

Application::~Application()
{
	delete keystate;
}

void Application::Init(void)
{
	if (!toolbar.LoadTGA("res/images/toolbar.tga")) std::cout << "Toolbar not found" << std::endl;;
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	// ...

	framebuffer.Render();
	for (int i = 0; i <= 50; i++) for (int j = 0; j < framebuffer.width; j++) framebuffer.SetPixelSafe(j, framebuffer.height - i, Color(51));
	framebuffer.DrawImagePixels(toolbar, 0, 0, true);
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	framebuffer.Resize(w, h);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	int r;
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_l: MODE = LINE; break;

	case SDLK_c: MODE = CIRCLE; break;

	case SDLK_d: MODE = FREEHAND; break;

	case SDLK_f: MODE = FILL_CIRCLE; break;

		// Backspace fills the canvas with white (erase)
	case SDLK_BACKSPACE: framebuffer.Fill(Color::WHITE); break;
	case SDLK_n: framebuffer.Fill(Color::WHITE); break;

	case SDLK_t: framebuffer.DrawImagePixels(toolbar, 0, 0, true); break;

	case SDLK_p: MODE = PARTICLE; break;

	case SDLK_s: if(framebuffer.SaveTGA("../../myDrawing.tga")) std::cout << "SAVED SUCCESSFULLY" << std::endl; break;

	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	bool onToolbar = (framebuffer.height - 50) < mouse_position.y;

	if (event.button == SDL_BUTTON_LEFT && !onToolbar) {
		LastClick = mouse_position;
		DRAWING = true;
	}
	else if (event.button == SDL_BUTTON_LEFT && onToolbar) {
		int i = 0;
		// "NEW" Button
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) framebuffer.Fill(Color::WHITE);

		i++;
		// "SAVE" Button
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50 && framebuffer.SaveTGA("../../myDrawing.tga")) std::cout << "SAVED SUCCESSFULLY" << std::endl;

		i++;
		// COLOR Buttons
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::BLACK; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::RED; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::GREEN; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::BLUE; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::YELLOW; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::PURPLE; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::CYAN; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { global_col = Color::WHITE; }
		i += 2;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { MODE = FREEHAND; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { MODE = LINE; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { MODE = CIRCLE; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { MODE = FILL_CIRCLE; }
		i++;
		if (i * 50 < mouse_position.x && mouse_position.x < (i + 1) * 50) { MODE = PARTICLE; }

	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	int r = (int)sqrt((mouse_position.x - LastClick.x) * (mouse_position.x - LastClick.x) + (mouse_position.y - LastClick.y) * (mouse_position.y - LastClick.y));
	bool onToolbar = mouse_position.x;
	if (event.button == SDL_BUTTON_LEFT && DRAWING) {
		switch (MODE) {
		case CIRCLE:
			framebuffer.DrawCircle(LastClick.x, LastClick.y, r, global_col, false);
			break;
		case FILL_CIRCLE:
			framebuffer.DrawCircle(LastClick.x, LastClick.y, r, global_col, true);
			break;
		case LINE:
			framebuffer.DrawLineBresenham(LastClick.x, LastClick.y, mouse_position.x, mouse_position.y, global_col);
			break;
		default:
			break;
		}
		DRAWING = false;
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (DRAWING && MODE == FREEHAND) {
		framebuffer.DrawLineBresenham(LastClick.x, LastClick.y, mouse_position.x, mouse_position.y, global_col);
		LastClick = mouse_position;
	}
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}