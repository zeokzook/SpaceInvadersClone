#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <SDL2/SDL.h>
#include <math.h>
#include <string>

#define Vector2f Vector2D<float>
#define Vector2 Vector2D<int>

template <typename T>
class Vector2D
{
public:
    T x = 0;
    T y = 0;
    T lower = x;
    T upper = y;

    Vector2D(){}
    Vector2D(T x, T y)
    {
        this->x = x;
        this->y = y;
        this->lower = x;
        this->upper = y;
    }

    Vector2D operator-(const Vector2D& other) const
    {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator+(const Vector2D& other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator*(const T& other) const
    {
        return Vector2D(x * other, y * other);
    }

    Vector2D operator*(const Vector2D& other) const
    {
        return Vector2D(x * other.x, y * other.y);
    }

    Vector2D& operator*=(float other)
    {
        x *= other;
        y *= other;

        return *this;
    }

    Vector2D& operator+=(float other)
    {
        x += other;
        y += other;

        return *this;
    }

    Vector2D& operator+=(Vector2D other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    bool operator==(const Vector2D& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2D& other) const
    {
        return x != other.x && y != other.y;
    }

    void Clamp(Vector2D other)
    {
        x = SDL_clamp(x, other.lower, other.upper);
        y = SDL_clamp(y, other.lower, other.upper);
    }

    float Length()
    {
        return std::sqrt((float)x*(float)x + (float)y*(float)y);
    }

    // Vector2D Normalize()
    // {
    //     Vector2D normalized;

    //     float len = Length();
    //     normalized.x = (T)x / (T)len;
    //     normalized.y = (T)y / (T)len;

    //     return normalized;
    // }

    Vector2D& NormalizeInPlace()
    {
        float len = Length();
        if(len <= 1.f)
            return *this;

        float newX = x / len;
        float newY = y / len;

        x = trunc(newX);
        y = trunc(newY);

        return *this;
    }
};

#endif // __VECTOR_H__