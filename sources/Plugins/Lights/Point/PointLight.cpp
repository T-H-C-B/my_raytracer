//
// Created by Clément Lagasse on 02/05/2023.
//

#include "PointLight.hpp"

RayTracer::Plugins::Lights::PointLight::PointLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color)
: ALight(position, rotation, intensity, color)
{
}

bool RayTracer::Plugins::Lights::PointLight::inView(const RayTracer::Shared::Vec3 &point) const
{
    return true;
}
