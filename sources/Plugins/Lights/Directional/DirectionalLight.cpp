//
// Created by Clément Lagasse on 02/05/2023.
//

#include "DirectionalLight.hpp"

RayTracer::Plugins::Lights::DirectionalLight::DirectionalLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color)
: ALight(position, rotation, intensity, color)
{
}

bool RayTracer::Plugins::Lights::DirectionalLight::inView(const RayTracer::Shared::Vec3 &point) const
{
    double NdotL = _direction.dot(point);

    return NdotL > 0.0;
}
