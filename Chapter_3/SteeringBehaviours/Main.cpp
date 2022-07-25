#include <iostream>
#include "SteeringBehavioursEnvironment.h"

int main(int, char**)
{
    SteeringBehavioursEnvironment env{};
    env.displayBehaviour(Behaviour::LookWhereYoureGoing);
    return 0;
}
