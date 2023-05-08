/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#include <cmath>
#include <iostream>
#include "Cylinder.hpp"

RayTracer::Plugins::Primitives::Cylinder::Cylinder(const RayTracer::Shared::Vec3& position, float radius)
: APrimitive(position, RayTracer::Shared::Vec3()), _radius(radius)
{
    std::cout << "Cylinder created" << std::endl;
}

void RayTracer::Plugins::Primitives::Cylinder::scale(float scale) {
    _radius *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Cylinder::intersect(const RayTracer::Shared::Ray& ray, float& t) const
{
    float a = ray.getDirection().x * ray.getDirection().x + ray.getDirection().z * ray.getDirection().z;
    float b = 2 * (ray.getDirection().x * (ray.getOrigin().x - _position.x) + ray.getDirection().z * (ray.getOrigin().z - _position.z));
    float c = (ray.getOrigin().x - _position.x) * (ray.getOrigin().x - _position.x) + (ray.getOrigin().z - _position.z) * (ray.getOrigin().z - _position.z) - _radius * _radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return std::nullopt;
    }

    float t0 = (-b - sqrt(discriminant)) / (2 * a);
    float t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 1e-4) {
        t0 = t1;
        if (t0 < 1e-4) 
          return std::nullopt;
    }

    t = t0;
    RayTracer::Shared::Vec3 hitPoint = ray.pointAt(t);
    RayTracer::Shared::Vec3 normal = (hitPoint - _position) / _radius;
    normal.y = 0;

    auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
    intersection->hit = true;
    intersection->t = t;
    intersection->point = hitPoint;
    intersection->normal = normal;
    intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;

    return std::optional<std::unique_ptr<RayTracer::Shared::Intersection>>(std::move(intersection));
}
