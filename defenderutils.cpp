#include "defenderutils.h"

#include "globals.h"

Defender::Vector2D Defender::getSmallestVectorTo(const Vector2D& from, const Vector2D& to)
{
    Vector2D vector1 = to - from;
    Vector2D vector2 = vector1 + Vector2D(worldWidth, 0);
    Vector2D vector3 = vector1 + Vector2D(-worldWidth, 0);
    double magnitude1 = vector1.magnitude();
    double magnitude2 = vector2.magnitude();
    double magnitude3 = vector3.magnitude();

    Vector2D* smallestVector = &vector1;
    double* smallestMagnitude = &magnitude1;

    if (magnitude2 < *smallestMagnitude)
    {
        smallestVector = &vector2;
        smallestMagnitude = &magnitude2;
    }

    if (magnitude3 < *smallestMagnitude)
    {
        smallestVector = &vector3;
        smallestMagnitude = &magnitude3;
    }

    return *smallestVector;
}
