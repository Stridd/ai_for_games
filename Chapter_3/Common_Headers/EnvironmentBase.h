#pragma once
#include "SDL.h"
#include "Behaviours.h"
#include "sdl_deleter.h"
#include <memory>
#include <string>

class EnvironmentBase
{

private:
	bool initSubsystems();

	bool createSDLComponents();

	bool createWindow();
	bool createRenderer();
	bool createSurface();

	virtual void renderObjects(	const float& textureRotation,
								const bool& drawTarget) const = 0;

protected:
	// Keep declaration of sdl_components as it is to destroy correctly.
	std::unique_ptr<SDL_Surface,	sdl_deleter>			screenSurface;
	std::unique_ptr<SDL_Renderer,	sdl_deleter>			renderer;
	std::unique_ptr<SDL_Window,		sdl_deleter>			window;

	bool isRunning;

	void setWindowName(const std::string& windowName);

public:
	EnvironmentBase();
	virtual ~EnvironmentBase();

	virtual void displayBehaviour(const Behaviour&) = 0;

	void handleEvents();
};

