// Plane.cpp

#include "Plane.hpp"
#include "Intersection.hpp"
#include <iostream>
#include <stdexcept>

RayTracer::Plugins::Primitives::Plane::Plane(const std::string &axis, float position, RayTracer::Shared::Material *material)
        : APrimitive(RayTracer::Shared::Vec3(), Shared::Vec3(), material), _axis(axis), _position(position)
{
    std::cout << "Plane created" << std::endl;
}
void RayTracer::Plugins::Primitives::Plane::scale(float scale) {
    _position *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Plane::intersect(const RayTracer::Shared::Ray &ray, float& t) const
{
    RayTracer::Shared::Vec3 normal;

    if (_axis == "X") {
        normal = RayTracer::Shared::Vec3(1, 0, 0);
    } else if (_axis == "Y") {
        normal = RayTracer::Shared::Vec3(0, 1, 0);
    } else if (_axis == "Z") {
        normal = RayTracer::Shared::Vec3(0, 0, 1);
    }

    float denominator = ray.getDirection().dot(normal);
    if (denominator > 1e-6) {
        RayTracer::Shared::Vec3 p0l0 = normal * _position - ray.getOrigin();
        float temp = p0l0.dot(normal) / denominator;
        if (temp > 1e-6 && temp < t) {
            t = temp;
            auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
            intersection->hit = true;
            intersection->t = t;
            intersection->point = ray.pointAt(t);
            intersection->normal = normal;
            return intersection;
        }
    }
    return std::nullopt;
}

