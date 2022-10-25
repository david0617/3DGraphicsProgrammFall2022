#include "Precompiled.h"
#include "../Inc/Constants.h"

constexpr double M::MMath::DegToRad(float degrees)
{
    return (degrees * (Pi / 180));
}

constexpr double M::MMath::RadToDeg(float radians)
{
    return(radians * (180 / Pi));
}