// AI_Implementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Environment.h"
#include "Behaviours.h"

int main(int, char** )
{
    Environment env{};
    env.displayBehaviour(Behaviour::KinematicArrive);
    return 0;
}