/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include <cmath>
#include <iostream>

RayTracer::Plugins::Primitives::Cylinder::Cylinder(const RayTracer::Shared::Vec3& position, float height, float radius, const RayTracer::Shared::Vec3& color)
: APrimitive(position, RayTracer::Shared::Vec3()), radius(radius), color(color)
{
    std::cout << "Cylinder created" << std::endl;
}

void RayTracer::Plugins::Primitives::Cylinder::scale(float scale) {
    radius *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Cylinder::intersect(const RayTracer::Shared::Ray& ray, float& t) const
{
    RayTracer::Shared::Vec3 oc = ray.getOrigin() - _position;
    RayTracer::Shared::Vec3 direction = ray.getDirection();

    float a = direction.x * direction.x + direction.z * direction.z;
    float b = 2.0f * (oc.x * direction.x + oc.z * direction.z);
    float c = oc.x * oc.x + oc.z * oc.z - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return std::nullopt;
    }

    float temp = (-b - sqrt(discriminant)) / (2.0f * a);
    if (temp < t) {
        t = temp;
        return std::nullopt;
    }

    temp = (-b + sqrt(discriminant)) / (2.0f * a);
    if (temp < t) {
        t = temp;
        return std::nullopt;
    }

    return std::nullopt;
}
