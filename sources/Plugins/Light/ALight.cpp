//
// Created by Clément Lagasse on 25/04/2023.
//

#include "ALight.hpp"

float RayTracer::Plugins::Lights::ALight::getIntensity() const
{
    return _intensity;
}

RayTracer::Shared::Vec3 &RayTracer::Plugins::Lights::ALight::getPosition() const
{
    return _position;
}
