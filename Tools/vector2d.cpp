#include "vector2d.h"
#include <assert.h>
#include <math.h>

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2D::~Vector2D()
{
    //dtor
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
