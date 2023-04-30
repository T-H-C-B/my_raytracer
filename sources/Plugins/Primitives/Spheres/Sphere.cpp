// Plane.cpp
//
// Created by Theophilus Homawoo on 30/04/2023.
//

#include <optional>
#include <iostream>
#include "AEntity.hpp"

RayTracer::Plugins::Primitives::Plane::Plane(const std::string& axis, float position, const RayTracer::Shared::Vec3& color)
        : APrimitive(RayTracer::Shared::Vec3(), RayTracer::Shared::Vec3()), axis(axis), position(position), color(color)
{
    std::cout << "Plane created" << std::endl;
}

void RayTracer::Plugins::Primitives::Plane::scale(float scale) {
    position *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Plane::intersect(const RayTracer::Shared::Ray &ray, float& t) const
{
    RayTracer::Shared::Vec3 normal;

    if (axis == "X") {
        normal = RayTracer::Shared::Vec3(1, 0, 0);
    } else if (axis == "Y") {
        normal = RayTracer::Shared::Vec3(0, 1, 0);
    } else if (axis == "Z") {
        normal = RayTracer::Shared::Vec3(0, 0, 1);
    } else {
        throw std::runtime_error("Invalid axis specified");
    }

    float denominator = ray.getDirection().dot(normal);
    if (denominator > 1e-6) {
        RayTracer::Shared::Vec3 p0l0 = position * normal - ray.getOrigin();
        float temp = p0l0.dot(normal) / denominator;
        if (temp > 1e-6 && temp < t) {
            t = temp;
            return std::nullopt;
        }
    }
    return std::nullopt;
}
