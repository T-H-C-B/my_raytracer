//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Vec2.hpp"

Vec2::Vec2(float x, float y) : x(x), y(y) {
}

Vec2::Vec2(int x, int y) : x(float(x)), y(float(y)) {
}

float Vec2::length() const {
    return sqrt(x * x + y * y);
}

Vec2 Vec2::normalize() const {
    float len = length();
    return {x / len, y / len};
}

Vec2 Vec2::operator+(const Vec2& other) const {
    return {x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return {x - other.x, y - other.y};
}

Vec2 Vec2::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

Vec2 Vec2::operator/(float scalar) const {
    return {x / scalar, y / scalar};
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vec2::operator==(const Vec2& other) const {
    return x == other.x && y == other.y;
}
