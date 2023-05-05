//
// Created by Clément Lagasse on 02/05/2023.
//

#include <cmath>
#include "DirectionalLight.hpp"

RayTracer::Plugins::Lights::DirectionalLight::DirectionalLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color)
: ALight(position, rotation, intensity, color)
{
}

bool RayTracer::Plugins::Lights::DirectionalLight::inView(const RayTracer::Shared::Vec3 &point) const
{
    RayTracer::Shared::Vec3 dist = point - _position;

    if (_direction.x != 0 && _direction.y != 0 && _direction.z != 0) {
        float ratio1 = dist.x / _direction.x;
        float ratio2 = dist.y / _direction.y;
        float ratio3 = dist.z / _direction.z;

        return fabs(ratio1 - ratio2) < 1e-6 && fabs(ratio2 - ratio3) < 1e-6;
    } 
    else {
        return false;
    }
}
