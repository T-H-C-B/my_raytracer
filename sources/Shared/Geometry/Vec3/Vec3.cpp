//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Vec3.hpp"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {
}

Vec3::Vec3(int x, int y, int z) : x(float(x)), y(float(y)), z(float(z)) {
}

float Vec3::length() const {
    return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const {
    float len = length();
    if (len == 0.0f) {
        return {0.0f, 0.0f, 0.0f};
    }
    return {x / len, y / len, z / len};
}

Vec3 Vec3::cross(const Vec3& other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Vec3 Vec3::operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vec3 Vec3::operator/(float scalar) const {
    return {x / scalar, y / scalar, z / scalar};
}

Vec3& Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3& Vec3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vec3::operator==(const Vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

float Vec3::dot(const Vec3 &vec3) const {
    return x * vec3.x + y * vec3.y + z * vec3.z;
}
