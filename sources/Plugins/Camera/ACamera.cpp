//
// Created by Clément Lagasse on 25/04/2023.
//

#include "ACamera.hpp"

EntityType RayTracer::Plugins::getType() const
{
    return EntityType::CAMERA;
}

void RayTracer::Plugins::setFov(float fov)
{
    _fov = fov;
}