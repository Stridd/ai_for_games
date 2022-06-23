#include <iostream>
#include <vector>
#include "Constants.h"
#include "Environment.h"
#include "AlgorithmBuilder.h"

Environment::Environment()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("GAME-AI-TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
    }

    std::vector<SDL_FPoint> points{
         SDL_FPoint{ 200, 250},
         SDL_FPoint{ 200, 300},
         SDL_FPoint{ 300, 275}
    };

    SDL_Color triangleColour{ 0, 0, 0, 255 };

    character = Character(points, triangleColour);

    target = SDL_FRect{ 1000, 500, 25, 25 };
}


void Environment::displayBehaviour(const Behaviour& behaviour)
{
    SDL_ShowWindow(window);

    SDL_Event e;

    bool gameIsRunning  = true;
    bool drawTarget     = true;

    if (behaviour == Behaviour::KinematicWander)
        drawTarget = false;

    AlgorithmBuilder builder(behaviour);

    while (gameIsRunning)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case(SDL_QUIT):
                {
                    gameIsRunning = false;
                    break;
                }
                case(SDL_MOUSEBUTTONDOWN):
                {
                    //character->rotate(90);
                    break;
                }
            }
        }

        float timeStep = stepTimer.getTicks() / 1000.f;

        KinematicSteeringOutput output{};

        switch (behaviour)
        {
            case(Behaviour::KinematicWander):
            {
                output = builder.getSteeringOutput(character);

                if (character.hasLeftOrientation())
                    output.velocity.x *= -1.0f;

                output.velocity *= timeStep;

                character.rotateRadians(output.rotation);

                character.move(output.velocity);

                character.calculateOrientation();

                break;
            }
            default:
            {
                output = builder.getSteeringOutput(character, target);
                output.velocity *= timeStep;

                if(!character.intersectsTarget(target))
                    character.move(output.velocity);
                break;
            }
        }

        stepTimer.start();

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderGeometry(renderer, nullptr, character.asVertex().data(), character.asVertex().size(), nullptr, 0);

        if (drawTarget)
        {
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0xFF);
            SDL_RenderFillRectF(renderer, &target);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
        SDL_RenderDrawLineF(renderer, character.points[0].x, 0, character.points[0].x, character.points[0].y);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0xFF);
        SDL_RenderDrawLineF(renderer, character.points[1].x, 0, character.points[1].x, character.points[1].y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0xFF);
        SDL_RenderDrawLineF(renderer, character.points[2].x, 0, character.points[2].x, character.points[2].y);

        SDL_RenderPresent(renderer);
    }

}

Environment::~Environment()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
