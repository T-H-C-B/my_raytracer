//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Vec3.hpp"

RayTracer::Shared::Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {
}

RayTracer::Shared::Vec3::Vec3(int x, int y, int z) : x(float(x)), y(float(y)), z(float(z)) {
}

float RayTracer::Shared::Vec3::length() const {
    return sqrt(x * x + y * y + z * z);
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::normalize() const {
    float len = length();
    if (len == 0.0f) {
        return {0.0f, 0.0f, 0.0f};
    }
    return {x / len, y / len, z / len};
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::cross(const Vec3& other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::operator/(float scalar) const {
    return {x / scalar, y / scalar, z / scalar};
}

RayTracer::Shared::Vec3& RayTracer::Shared::Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

RayTracer::Shared::Vec3& RayTracer::Shared::Vec3::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

RayTracer::Shared::Vec3& RayTracer::Shared::Vec3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

RayTracer::Shared::Vec3& RayTracer::Shared::Vec3::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool RayTracer::Shared::Vec3::operator==(const Vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

float RayTracer::Shared::Vec3::dot(const Vec3 &vec3) const {
    return x * vec3.x + y * vec3.y + z * vec3.z;
}

RayTracer::Shared::Vec3& RayTracer::Shared::Vec3::operator=(const RayTracer::Shared::Vec3& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

RayTracer::Shared::Vec3 RayTracer::Shared::operator*(float scalar, const RayTracer::Shared::Vec3& vec) {
    return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

float RayTracer::Shared::Vec3::degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0f;
}

RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::rotate(const Vec3& rotation) const {
    float rx = rotation.x * (M_PI / 180);
    float ry = rotation.y * (M_PI / 180);
    float rz = rotation.z * (M_PI / 180);

    float sinX = sin(rx), cosX = cos(rx);
    float sinY = sin(ry), cosY = cos(ry);
    float sinZ = sin(rz), cosZ = cos(rz);

    float y1 = y * cosX - z * sinX;
    float z1 = y * sinX + z * cosX;

    float x2 = x * cosY + z1 * sinY;
    float z2 = -x * sinY + z1 * cosY;

    float x3 = x2 * cosZ - y1 * sinZ;
    float y3 = x2 * sinZ + y1 * cosZ;

    return Vec3(x3, y3, z2);
}


RayTracer::Shared::Vec3 RayTracer::Shared::Vec3::inverseRotate(const Vec3& angles) const {
    float radX = -degreesToRadians(angles.x);
    float radY = -degreesToRadians(angles.y);
    float radZ = -degreesToRadians(angles.z);

    float cosX = cos(radX);
    float sinX = sin(radX);
    float cosY = cos(radY);
    float sinY = sin(radY);
    float cosZ = cos(radZ);
    float sinZ = sin(radZ);

    Vec3 rotated;
    rotated.x = cosY * (sinZ * y + cosZ * x) - sinY * z;
    rotated.y = sinX * (cosY * z + sinY * (sinZ * y + cosZ * x)) + cosX * (cosZ * y - sinZ * x);
    rotated.z = cosX * (cosY * z + sinY * (sinZ * y + cosZ * x)) - sinX * (cosZ * y - sinZ * x);

    return rotated;
}