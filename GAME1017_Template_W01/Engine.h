#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

// Do not include any macros, initialized properties or full function definitions in this header.

class Engine
{
public: // Public methods.
	int Run();
	static Engine& Instance(); // This static method creates the static instance that can be accessed 'globally'
	SDL_Renderer* GetRenderer(); //get the renderer globally
	bool& Running();

private: // Private properties.
	bool m_running; // Loop control flag.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; 
	SDL_Renderer* m_pRenderer; 
	


private: // Private methods.
	Engine(); //making the constructor private so there will be only one instance
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

};

#endif