#pragma once
#include "SDL.h"
#include "LTimer.h"
#include "Character.h"
#include "Behaviours.h"

class Environment
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	LTimer stepTimer;

	Character character;

	SDL_FRect target;

public:
	Environment();
	~Environment();

	void displayBehaviour(const Behaviour&);

};

