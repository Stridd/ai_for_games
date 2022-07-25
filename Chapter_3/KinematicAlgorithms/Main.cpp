// AI_Implementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "KinematicAlgorithmsEnvironment.h"
#include "Behaviours.h"
#include <HelperFunctions.h>

int main(int, char** )
{
    KinematicAlgorithmsEnvironment env{};
    env.displayBehaviour(Behaviour::KinematicWander);
    return 0;
}