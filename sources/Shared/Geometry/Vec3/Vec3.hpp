//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_VEC3_HPP
#define RAYTRACING_VEC3_HPP

#include <cmath>

class Vec3 {
    public:
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        Vec3(int x, int y, int z);

        float length() const;
        Vec3 normalize() const;
        Vec3 cross(const Vec3& other) const;
        float dot(const Vec3 &vec3) const;

        Vec3 operator*(float scalar) const;
        Vec3 operator/(float scalar) const;
        Vec3 operator+(const Vec3& other) const;
        Vec3 operator-(const Vec3& other) const;
        Vec3& operator+=(const Vec3& other);
        Vec3& operator-=(const Vec3& other);
        Vec3& operator*=(float scalar);
        Vec3& operator/=(float scalar);
        bool operator==(const Vec3& other) const;

        float x;
        float y;
        float z;
};


#endif //RAYTRACING_VEC3_HPP
