#include "math.h"

bool IsOverlappingBox(const BoxCollider& a, const BoxCollider& b)
{
    const Vector2 minA = *a.pivot;
    const Vector2 maxA = minA + a.size;
   
    const Vector2 minB = *b.pivot;
    const Vector2 maxB = minB + b.size;

    return !(
        maxA.x < minB.x || minA.x > maxB.x || 
        maxA.y < minB.y || minA.y > maxB.y
    );
}