//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Ray.hpp"

RayTracer::Shared::Ray::Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {
}

const RayTracer::Shared::Vec3 &RayTracer::Shared::Ray::getOrigin() const {
    return origin;
}

const RayTracer::Shared::Vec3 RayTracer::Shared::Ray::getDirection() const {
    return direction;
}

RayTracer::Shared::Vec3 RayTracer::Shared::Ray::pointAt(float t) const {
    return origin + direction * t;
}
