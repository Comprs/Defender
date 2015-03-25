#include "defenderutils.h"

#include "globals.h"

Defender::Vector2D Defender::getSmallestVectorTo(const Vector2D& from, const Vector2D& to)
{
    // Get the possible vector results
    Vector2D vector1 = to - from;
    Vector2D vector2 = vector1 + Vector2D(worldWidth, 0);
    Vector2D vector3 = vector1 + Vector2D(-worldWidth, 0);

    // Get their magnitudes
    double magnitude1 = vector1.magnitude();
    double magnitude2 = vector2.magnitude();
    double magnitude3 = vector3.magnitude();

    // Initially assume the first one is the smallest and instantiate the holding
    // variables with a pointer to them
    Vector2D* smallestVector = &vector1;
    double* smallestMagnitude = &magnitude1;

    // Compare with the second
    if (magnitude2 < *smallestMagnitude)
    {
        // If it is smaller, reassign the holding variables
        smallestVector = &vector2;
        smallestMagnitude = &magnitude2;
    }

    // Compare with the third
    if (magnitude3 < *smallestMagnitude)
    {
        smallestVector = &vector3;
        smallestMagnitude = &magnitude3;
    }

    return *smallestVector;
}
