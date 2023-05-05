//
// Created by Theophilus Homawoo on 15/04/2023.
//

// Sphere.cpp

#include <optional>
#include <iostream>
#include "AEntity.hpp"
#include "Material.hpp"
#include "Sphere.hpp"

RayTracer::Plugins::Primitives::Sphere::Sphere(const RayTracer::Shared::Vec3& position, float radius)
: APrimitive(position, RayTracer::Shared::Vec3()), radius(radius)
{
    std::cout << "Sphere created" << std::endl;
}

void RayTracer::Plugins::Primitives::Sphere::scale(float scale) {
    radius *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Sphere::intersect(const RayTracer::Shared::Ray &ray, float& t) const
{
    Shared::Vec3 oc = ray.getOrigin() - _position;
    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2.0f * oc.dot(ray.getDirection());
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        bool found_intersection = false;

        float temp = (-b - sqrt(discriminant)) / (2.0f * a);
        if (temp > 1e-4 && temp < t) {
            t = temp;
            found_intersection = true;
        }

        temp = (-b + sqrt(discriminant)) / (2.0f * a);
        if (temp > 1e-4 && temp < t) {
            if (temp < t) {
                t = temp;
            }
            found_intersection = true;
        }

        if (found_intersection) {
            auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
            intersection->hit = true;
            intersection->t = t;
            intersection->point = ray.pointAt(t);
            intersection->normal = (intersection->point - _position);
            return intersection;
        }
    }

    return std::nullopt;
}

