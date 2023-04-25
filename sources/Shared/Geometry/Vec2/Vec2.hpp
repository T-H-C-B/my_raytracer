//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_VEC2_HPP
#define RAYTRACING_VEC2_HPP

#include <cmath>

namespace RayTracer {
    class Vec2 {
    public:
        Vec2(float x = 0.0f, float y = 0.0f);
        Vec2(int x, int y);

        float length() const;
        Vec2 normalize() const;

        Vec2 operator*(float scalar) const;
        Vec2 operator/(float scalar) const;
        Vec2 operator+(const Vec2& other) const;
        Vec2 operator-(const Vec2& other) const;
        Vec2& operator+=(const Vec2& other);
        Vec2& operator-=(const Vec2& other);
        Vec2& operator*=(float scalar);
        Vec2& operator/=(float scalar);
        bool operator==(const Vec2& other) const;

        float x;
        float y;
    };
}


#endif //RAYTRACING_VEC2_HPP
