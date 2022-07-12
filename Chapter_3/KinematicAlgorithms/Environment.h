#pragma once
#include "SDL.h"
#include "Character.h"
#include "Behaviours.h"

class Environment
{

private:
	std::unique_ptr<SDL_Window,		sdl_deleter>		window;
	std::unique_ptr<SDL_Renderer,	sdl_deleter>		renderer;
	std::unique_ptr<SDL_Surface,	sdl_deleter>		screenSurface;

	Character character;
	std::unique_ptr<Character> target;
	
	bool isRunning;

	bool initSubsystems();

	bool createSDLComponents();

	bool createWindow();
	bool createRenderer();
	bool createSurface();

	bool createCharacters();

	void RenderCharacters(const float& textureRotation, 
							const bool& drawTarget);

public:
	Environment();
	~Environment();

	void displayBehaviour(const Behaviour&);

	void HandleEvents();
};

