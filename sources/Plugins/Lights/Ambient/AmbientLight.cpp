//
// Created by Clément Lagasse on 02/05/2023.
//

#include "AmbientLight.hpp"

RayTracer::Plugins::Lights::AmbientLight::AmbientLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color)
: ALight(position, rotation, intensity, color)
{
}

bool RayTracer::Plugins::Lights::AmbientLight::inView(const RayTracer::Shared::Vec3 &point) const
{
    return true;
}
