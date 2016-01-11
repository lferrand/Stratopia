#include "vector2d.h"
#include "tools.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>


Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2D::~Vector2D()
{
    //dtor
}

Vector2D Vector2D::Normalized()
{
    if(Length() != 0){
        Vector2D normalized = Vector2D(x/Length(),y/Length());
        return normalized;
    }
    return *this;
}

Vector2D Vector2D::RotateByAngle(float angle)
{
    Vector2D rotated;
    rotated.x =(x * cos(angle))-(y * sin(angle));
    rotated.y =(x * sin(angle))-(y * cos(angle));
    return rotated;
}

float Vector2D::Length()
{
    return (float)sqrt( pow(x,2)+pow(y,2) );
}
void Vector2D::Truncate(float upperBound)
{
    float lenght = Length();
    if(lenght > upperBound)
    {
        float mult = upperBound/lenght;
        x *= mult;
        y *= mult;
    }
}

Vector2D& Vector2D::operator= (const Vector2D &other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D& Vector2D::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(float scalar)
{
	assert(scalar != 0.0f);
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2D operator+ (const Vector2D &a, const Vector2D &b)
{
	return Vector2D(a.x + b.x, a.y + b.y);
}
Vector2D operator+ (const Vector2D* &a, const Vector2D &b)
{
	return Vector2D(a->x + b.x, a->y + b.y);
}

Vector2D operator- (const Vector2D &a, const Vector2D &b)
{
	return Vector2D(a.x - b.x, a.y - b.y);
}

Vector2D operator* (const Vector2D &a, float scalar)
{
	return Vector2D(a.x * scalar, a.y * scalar);
}

Vector2D operator* (float scalar, const Vector2D &a)
{
	return Vector2D(a.x * scalar, a.y * scalar);
}

Vector2D operator/ (const Vector2D &a, float divisor)
{
	assert(divisor != 0.0f);
	return Vector2D(a.x / divisor, a.y / divisor);
}
