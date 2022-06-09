// AI_Implementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#include <SDL_render.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Triangle.h"

//Screen dimension constants
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

constexpr double DISTANCETHRESHOLD = 20;

// Taken from LazyFoo SDL Tutorial, lesson 44

//The application time based timer
class LTimer
{
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};

LTimer::LTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if (mStarted && !mPaused)
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if (mStarted && mPaused)
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (mStarted)
    {
        //If the timer is paused
        if (mPaused)
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}


int main(int argc, char* argv[])
{
    //The window we'll be rendering to
    SDL_Window* window      = nullptr;
    SDL_Renderer* renderer  = nullptr;

    //The surface contained by the window
    SDL_Surface* screenSurface = nullptr;

   std::vector<SDL_FPoint> points{
        SDL_FPoint{ 200, 250},
        SDL_FPoint{ 200, 300},
        SDL_FPoint{ 300, 275 }
    };

    SDL_Color triangleColour{ 0, 0, 0, 255 };

    Triangle triangle{points, triangleColour};

    SDL_FRect target{ 1000, 600, 25, 25};

    LTimer stepTimer;

    float fakeTime = 1.0;


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Game AI Behaviour", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            bool gameIsRunning = true;
            int red_color = 0;

            SDL_Event e;
            while (gameIsRunning)
            {

                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        gameIsRunning = false;
                    }
                }

                float timeStep = stepTimer.getTicks() / 1000.f;

                if (!triangle.intersectsTarget(target))
                    triangle.Seek(target, timeStep);

                stepTimer.start();

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                SDL_RenderGeometry(renderer, nullptr, triangle.asVertex().data(), triangle.asVertex().size(), nullptr, 0);

                SDL_SetRenderDrawColor(renderer, 128, 128, 0, 0xFF);
                SDL_RenderFillRectF(renderer, &target);

     /*         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
                SDL_RenderDrawLine(renderer, triangle.asVertex()[0].position.x, 0, triangle.asVertex()[0].position.x, triangle.asVertex()[0].position.y);

                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0xFF);
                SDL_RenderDrawLine(renderer, triangle.asVertex()[1].position.x, 0, triangle.asVertex()[1].position.x, triangle.asVertex()[1].position.y);

                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0xFF);
                SDL_RenderDrawLine(renderer, triangle.asVertex()[2].position.x, 0, triangle.asVertex()[2].position.x, triangle.asVertex()[2].position.y);*/
                

                SDL_RenderPresent(renderer);
                //triangle.rotate(10);
               
            }

            SDL_DestroyRenderer(renderer);
        }
    }


    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}