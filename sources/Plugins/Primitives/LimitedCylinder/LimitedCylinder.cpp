/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** LimitedCylinder
*/

#include <cmath>
#include <iostream>
#include <memory>
#include "LimitedCylinder.hpp"

RayTracer::Plugins::Primitives::LimitedCylinder::LimitedCylinder(const RayTracer::Shared::Vec3& position, float radius, const RayTracer::Shared::Vec3& rotation, int height)
: APrimitive(position, rotation), _radius(radius), _height(height), _rotation(rotation)
{
    std::cout << "LimitedCylinder created" << std::endl;
}

void RayTracer::Plugins::Primitives::LimitedCylinder::scale(float scale) {
    _radius *= scale;
    _height *= scale;
}

std::optional<float> RayTracer::Plugins::Primitives::LimitedCylinder::cylIntersect(const RayTracer::Shared::Ray &ray, const RayTracer::Shared::Vec3 &a, const RayTracer::Shared::Vec3 &b, float ra) const {
    RayTracer::Shared::Vec3 ro = ray.getOrigin();
    RayTracer::Shared::Vec3 rd = ray.getDirection();

    RayTracer::Shared::Vec3 ba = b - a;
    RayTracer::Shared::Vec3 oc = ro - a;
    float baba = ba.dot(ba);
    float bard = ba.dot(rd);
    float baoc = ba.dot(oc);
    float k2 = baba - bard * bard;
    float k1 = baba * oc.dot(rd) - baoc * bard;
    float k0 = baba * oc.dot(oc) - baoc * baoc - ra * ra * baba;
    float h = k1 * k1 - k2 * k0;
    if (h < 0.0) return std::nullopt;

    h = sqrt(h);
    float t = (-k1 - h) / k2;

    float y = baoc + t * bard;
    if (y > 0.0 && y < baba) return t;

    t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
    if (fabs(k1 + k2 * t) < h) return t;

    return std::nullopt;
}

RayTracer::Shared::Vec3 RayTracer::Plugins::Primitives::LimitedCylinder::cylNormal(const RayTracer::Shared::Vec3 &p, const RayTracer::Shared::Vec3 &a, const RayTracer::Shared::Vec3 &b, float ra) const {
    RayTracer::Shared::Vec3 pa = p - a;
    RayTracer::Shared::Vec3 ba = b - a;
    float baba = ba.dot(ba);
    float paba = pa.dot(ba);
    float h = pa.dot(ba) / baba;
    return (pa - ba * h) / ra;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::LimitedCylinder::intersect(const RayTracer::Shared::Ray &ray, float &t) const {
    RayTracer::Shared::Vec3 a = _position;
    RayTracer::Shared::Vec3 b = _position + RayTracer::Shared::Vec3(0, _height, 0);

    auto t_result = cylIntersect(ray, a, b, _radius);
    if (!t_result) return std::nullopt;

    t = *t_result;
    RayTracer::Shared::Vec3 hitPoint = ray.getOrigin() + ray.getDirection() * t;

    auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
    intersection->hit = true;
    intersection->point = hitPoint;
    intersection->normal = cylNormal(hitPoint, a, b, _radius);
    intersection->t = t;
    intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;

    return intersection;
}
