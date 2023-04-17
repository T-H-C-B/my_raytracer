//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Ray.hpp"

Ray::Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {
}

const Vec3 &Ray::getOrigin() const {
    return origin;
}

const Vec3 Ray::getDirection() const {
    return direction;
}

Vec3 Ray::pointAt(float t) const {
    return origin + direction * t;
}
