//
// Created by Clément Lagasse on 02/05/2023.
//

#include <cmath>
#include "DirectionalLight.hpp"

RayTracer::Plugins::Lights::DirectionalLight::DirectionalLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &direction, float intensity, const RayTracer::Shared::Vec3 &color)
: ALight(position, RayTracer::Shared::Vec3(), intensity, color)
{
    setDirection(direction);
}

bool RayTracer::Plugins::Lights::DirectionalLight::inView(const RayTracer::Shared::Vec3 &point) const
{
    RayTracer::Shared::Vec3 normalizedPoint = point;
    normalizedPoint.normalize();

    float cosAngle = normalizedPoint.dot(_direction);

    return cosAngle > 0;
}
