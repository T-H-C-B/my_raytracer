/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cone
*/

#include <cmath>
#include <iostream>
#include "Cone.hpp"


RayTracer::Plugins::Primitives::Cone::Cone(const RayTracer::Shared::Vec3& position, float radius, const RayTracer::Shared::Vec3& rotation, int height)
: APrimitive(position, rotation), _radius(radius), _rotation(rotation), _height(height)
{
    std::cout << "Cone created" << std::endl;
}

void RayTracer::Plugins::Primitives::Cone::scale(float scale) {
    _radius *= scale;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Cone::intersect(const RayTracer::Shared::Ray &ray, float& t) const
{
    RayTracer::Shared::Vec3 rotatedOrigin = (ray.getOrigin() - _position).inverseRotate(_rotation);
    RayTracer::Shared::Vec3 rotatedDirection = ray.getDirection().inverseRotate(_rotation);
    RayTracer::Shared::Ray rotatedRay(rotatedOrigin, rotatedDirection);

    float a = rotatedRay.getDirection().x * rotatedRay.getDirection().x + rotatedRay.getDirection().z * rotatedRay.getDirection().z - rotatedRay.getDirection().y * rotatedRay.getDirection().y;
    float b = 2 * ((rotatedRay.getDirection().x * (rotatedRay.getOrigin().x - _position.x) + rotatedRay.getDirection().z * (rotatedRay.getOrigin().z - _position.z)) - rotatedRay.getDirection().y * (rotatedRay.getOrigin().y - _position.y));
    float c = (rotatedRay.getOrigin().x - _position.x) * (rotatedRay.getOrigin().x - _position.x) + (rotatedRay.getOrigin().z - _position.z) * (rotatedRay.getOrigin().z - _position.z) - (rotatedRay.getOrigin().y - _position.y) * (rotatedRay.getOrigin().y - _position.y);

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return std::nullopt;
    }

    float t0 = (-b - sqrt(discriminant)) / (2 * a);
    float t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 1e-4) {
        t0 = t1;
        if (t0 < 1e-4) return std::nullopt;
    }

    t = t0;
    RayTracer::Shared::Vec3 hitPoint = rotatedRay.pointAt(t);
    RayTracer::Shared::Vec3 normal = (hitPoint - _position);
    normal.y = -normal.y;

    if (hitPoint.y < _position.y) {
        return std::nullopt;
    }
    
    auto baseIntersection = intersectBase(ray, t);

    if (_height > 0 && hitPoint.y > _position.y + _height) {
        if (baseIntersection) {
            std::unique_ptr<RayTracer::Shared::Intersection> intersect = std::move(baseIntersection.value());
            t = intersect->t;
            return intersect;
        }
        return std::nullopt;
    }

    auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
    intersection->hit = true;
    intersection->t = t;
    intersection->point = hitPoint;
    intersection->normal = normal.normalize();
    intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;

    if (baseIntersection) {
        std::unique_ptr<RayTracer::Shared::Intersection> intersect = std::move(baseIntersection.value());
        if (intersect->t < intersection->t) {
            t = intersect->t;
            return intersect;
        }
    }

    return std::optional<std::unique_ptr<RayTracer::Shared::Intersection>>(std::move(intersection));
}


std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Cone::intersectBase(const RayTracer::Shared::Ray &ray, float& t) const
{
    float denom = ray.getDirection().dot(RayTracer::Shared::Vec3(0, 1, 0));
    if (std::abs(denom) < 1e-6) {
        return std::nullopt;
    }

    float tBase = (_position.y - ray.getOrigin().y) / denom;
    if (tBase < 0) {
        return std::nullopt;
    }

    RayTracer::Shared::Vec3 hitPoint = ray.pointAt(tBase);
    float distToCenterSquared = (hitPoint.x - _position.x) * (hitPoint.x - _position.x) + (hitPoint.z - _position.z) * (hitPoint.z - _position.z);
    if (distToCenterSquared > _radius * _radius) {
        return std::nullopt;
    }

    auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
    intersection->hit = true;
    intersection->t = tBase;
    intersection->point = hitPoint;
    intersection->normal = RayTracer::Shared::Vec3(0, 1, 0);
    intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;

    std::cout << "intersection at base" << std::endl;

    return std::optional<std::unique_ptr<RayTracer::Shared::Intersection>>(std::move(intersection));
}