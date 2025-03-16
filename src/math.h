#pragma once


struct Vector2
{
    float x;
    float y;

    Vector2 operator+(const Vector2& other) const {
        return Vector2{x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2{x - other.x, y - other.y};
    }

    Vector2 operator*(float scalar) const {
        return Vector2{x * scalar, y * scalar};
    }
};

struct BoxCollider
{
    Vector2* pivot;
    Vector2 size;
};

bool IsOverlappingBox(const BoxCollider& a, const BoxCollider& b);