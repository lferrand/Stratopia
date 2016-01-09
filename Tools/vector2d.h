#ifndef VECTOR2D_H
#define VECTOR2D_H


class Vector2D
{
    public:
        float x;
        float y;
        Vector2D(float x, float y);
        virtual ~Vector2D();
        Vector2D& operator= (const Vector2D &other);
        Vector2D& operator+=(const Vector2D &other);
        Vector2D& operator-=(const Vector2D &other);
        Vector2D& operator*=(float scalar);
        Vector2D& operator/=(float scalar);
    protected:
    private:
};

#endif // VECTOR2D_H
