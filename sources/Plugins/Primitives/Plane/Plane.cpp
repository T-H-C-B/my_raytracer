// Plane.cpp

#include <iostream>
#include <stdexcept>
#include "Plane.hpp"
#include "Intersection.hpp"
#include "Vec3.hpp"

RayTracer::Plugins::Primitives::Plane::Plane(RayTracer::Shared::Vec3 &position, RayTracer::Shared::Vec3 &normal)
: APrimitive(position, Shared::Vec3()), _normal(normal)
{
    std::cout << "Plane created" << std::endl;
}

void RayTracer::Plugins::Primitives::Plane::scale(float scale) {
    _position *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Plane::intersect(const RayTracer::Shared::Ray &ray, float& t) const
{
    float denominator = ray.getDirection().dot(_normal);
    if (std::abs(denominator) > 1e-6) {
        float temp = (_position - ray.getOrigin()).dot(_normal) / denominator;
        if (temp > 1e-6 && temp < t) {
            t = temp;
            auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
            intersection->hit = true;
            intersection->t = t;
            intersection->point = ray.pointAt(t);
            intersection->normal = _normal;
            return intersection;
        }
    }
    return std::nullopt;
}

