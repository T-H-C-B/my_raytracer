/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Torus
*/

#include <cmath>
#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <numeric>
#include "Torus.hpp"

RayTracer::Plugins::Primitives::Torus::Torus(const RayTracer::Shared::Vec3& position, float majorRadius, float minorRadius, const RayTracer::Shared::Vec3& rotation)
: APrimitive(position, rotation), _majorRadius(majorRadius), _minorRadius(minorRadius), _rotation(rotation)
{
    std::cout << "Torus created" << std::endl;
}

void RayTracer::Plugins::Primitives::Torus::scale(float scale) {
    _majorRadius *= scale;
    _minorRadius *= scale;
}

float RayTracer::Plugins::Primitives::Torus::torIntersect(const RayTracer::Shared::Ray& ray) const {
    RayTracer::Shared::Vec3 ro = ray.getOrigin();
    RayTracer::Shared::Vec3 rd = ray.getDirection();

    float po = 1.0f;
    float Ra2 = _majorRadius * _majorRadius;
    float ra2 = _minorRadius * _minorRadius;
    float m = ro.dot(ro);
    float n = ro.dot(rd);
    float k = (m + Ra2 - ra2) / 2.0f;
    float k3 = n;
    float k2 = n * n - Ra2 * rd.x * rd.x + k;
    float k1 = n * k - Ra2 * rd.x * ro.x;
    float k0 = k * k - Ra2 * ro.x * ro.x;

    if (std::abs(k3 * (k3 * k3 - k2) + k1) < 0.01f) {
        po = -1.0f;
        std::swap(k1, k3);
        k0 = 1.0f / k0;
        k1 = k1 * k0;
        k2 = k2 * k0;
        k3 = k3 * k0;
    }

    float c2 = k2 * 2.0f - 3.0f * k3 * k3;
    float c1 = k3 * (k3 * k3 - k2) + k1;
    float c0 = k3 * (k3 * (c2 + 2.0f * k2) - 8.0f * k1) + 4.0f * k0;
    c2 /= 3.0f;
    c1 *= 2.0f;
    c0 /= 3.0f;
    float Q = c2 * c2 + c0;
    float R = c2 * c2 * c2 - 3.0f * c2 * c0 + c1 * c1;
    float h = R * R - Q * Q * Q;

    if (h >= 0.0f) {
        h = std::sqrt(h);
        float v = std::copysign(std::pow(std::abs(R + h), 1.0f / 3.0f), R + h);
        float u = std::copysign(std::pow(std::abs(R - h), 1.0f / 3.0f), R - h);
        RayTracer::Shared::Vec3 s = RayTracer::Shared::Vec3((v + u) + 4.0f * c2, (v - u) * std::sqrt(3.0f), 0.0f);
        float y = std::sqrt(0.5f * (s.length() + s.x));
        float x = 0.5f * s.y / y;
        float r = 2.0f * c1 / (x * x + y * y);
        float t1 = x - r - k3;
        t1 = (po < 0.0f) ? 2.0f / t1 : t1;
        float t2 = -x - r - k3;
                t2 = (po < 0.0f) ? 2.0f / t2 : t2;
        float t = 1e20f;
        if (t1 > 0.0f) t = t1;
        if (t2 > 0.0f) t = std::min(t, t2);
        return t;
    }

    float sQ = std::sqrt(Q);
    float w = sQ * std::cos(std::acos(-R / (sQ * Q)) / 3.0f);
    float d2 = -(w + c2);
    if (d2 < 0.0f) return -1.0f;
    float d1 = std::sqrt(d2);
    float h1 = std::sqrt(w - 2.0f * c2 + c1 / d1);
    float h2 = std::sqrt(w - 2.0f * c2 - c1 / d1);
    float t1 = -d1 - h1 - k3;
    t1 = (po < 0.0f) ? 2.0f / t1 : t1;
    float t2 = -d1 + h1 - k3;
    t2 = (po < 0.0f) ? 2.0f / t2 : t2;
    float t3 = d1 - h2 - k3;
    t3 = (po < 0.0f) ? 2.0f / t3 : t3;
    float t4 = d1 + h2 - k3;
    t4 = (po < 0.0f) ? 2.0f / t4 : t4;
    float t = 1e20f;
    if (t1 > 0.0f) t = t1;
    if (t2 > 0.0f) t = std::min(t, t2);
    if (t3 > 0.0f) t = std::min(t, t3);
    if (t4 > 0.0f) t = std::min(t, t4);
    return t;
}

RayTracer::Shared::Vec3  RayTracer::Plugins::Primitives::Torus::torNormal(const RayTracer::Shared::Vec3& pos) const {
    RayTracer::Shared::Vec3 adjustedPos = pos;
    adjustedPos.z *= -1.0f;
    float squaredLength = pos.dot(pos) - _minorRadius * _minorRadius;
    RayTracer::Shared::Vec3 scalingVec(_majorRadius * _majorRadius, _majorRadius * _majorRadius, -_majorRadius * _majorRadius);
    RayTracer::Shared::Vec3 result = (RayTracer::Shared::Vec3(squaredLength, squaredLength, squaredLength) - scalingVec);
    return RayTracer::Shared::Vec3(adjustedPos.x * result.x, adjustedPos.y * result.y, adjustedPos.z * result.z).normalize();
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Torus::intersect(const RayTracer::Shared::Ray& ray, float& t) const {
    RayTracer::Shared::Vec3 rotatedOrigin = ray.getOrigin().inverseRotate(_rotation);
    RayTracer::Shared::Vec3 rotatedDirection = ray.getDirection().inverseRotate(_rotation);
    RayTracer::Shared::Ray rotatedRay(rotatedOrigin, rotatedDirection);

    float intersectionT = torIntersect(rotatedRay);

    if (intersectionT < 0.0f) {
        return std::nullopt;
    }

    t = intersectionT;
    RayTracer::Shared::Vec3 localHitPoint = rotatedRay.pointAt(t);
    RayTracer::Shared::Vec3 hitPoint = localHitPoint.rotate(_rotation) + _position;
    RayTracer::Shared::Vec3 localNormal = torNormal(localHitPoint);
    RayTracer::Shared::Vec3 normal = localNormal.rotate(_rotation);

    auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
    intersection->hit = true;
    intersection->t = t;
    intersection->point = hitPoint;
    intersection->normal = normal;
    intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;

    return std::optional<std::unique_ptr<RayTracer::Shared::Intersection>>(std::move(intersection));
}
