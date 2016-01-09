#ifndef VECTOR2D_H
#define VECTOR2D_H


class Vector2D
{
    public:
        float x;
        float y;
        Vector2D();
        Vector2D(float x, float y);
        virtual ~Vector2D();
        Vector2D& operator= (const Vector2D &other);
        Vector2D& operator+=(const Vector2D &other);
        Vector2D& operator-=(const Vector2D &other);
        Vector2D& operator*=(float scalar);
        Vector2D& operator/=(float scalar);
        Vector2D Normalized();
    protected:
    private:
};

Vector2D operator+ (const Vector2D &a, const Vector2D &b);
Vector2D operator- (const Vector2D &a, const Vector2D &b);
Vector2D operator* (const Vector2D &a, float scalar);
Vector2D operator* (float scalar, const Vector2D &a);
Vector2D operator/ (const Vector2D &a, float divisor);
#endif // VECTOR2D_H
