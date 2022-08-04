#pragma once

#include <memory>
#include <string>

#include "SDL.h"
#include "Behaviours.h"
#include "sdl_deleter.h"
#include "json.hpp"

using json = nlohmann::json;

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

	Algorithm::Behaviour algorithmBehaviour;

	json configData;

	bool isRunning;

	void setWindowName(const std::string& windowName);

public:
	EnvironmentBase();
	virtual ~EnvironmentBase();

	virtual void displayBehaviour() = 0;

	void handleEvents();
};

