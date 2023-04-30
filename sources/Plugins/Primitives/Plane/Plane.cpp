//
// Created by Theophilus Homawoo on 15/04/2023.
//

#include <optional>
#include <iostream>
#include "AEntity.hpp"
#include "Plane.hpp"

RayTracer::Plugins::Primitives::Sphere::Sphere(const RayTracer::Shared::Vec3& position, float radius, const  RayTracer::Shared::Vec3& color)
: APrimitive(position, RayTracer::Shared::Vec3()), radius(radius), color(color)
{
    std::cout << "Sphere created" << std::endl;
}

void RayTracer::Plugins::Primitives::Sphere::scale(float scale) {
    radius *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>>  RayTracer::Plugins::Primitives::Sphere::intersect(const RayTracer::Shared::Ray &ray, float& t) const
{
    RayTracer::Shared::Vec3 oc = ray.getOrigin() - _position;
    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2.0f * oc.dot(ray.getDirection());
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / (2.0f * a);
        if (temp > 1e-4 && temp < t) {
            t = temp;
            return std::nullopt;
        }
        temp = (-b + sqrt(discriminant)) / (2.0f * a);
        if (temp > 1e-4 && temp < t) {
            t = temp;
            return std::nullopt;
        }
    }
    return std::nullopt;
}
