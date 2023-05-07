//
// Created by Clément Lagasse on 05/05/2023.
//

#include "ACamera.hpp"

RayTracer::Shared::Vec3 RayTracer::Plugins::Cameras::ACamera::getRightVector() const
{
    RayTracer::Shared::Vec3 up = RayTracer::Shared::Vec3(1.0f, 0.0f, 0.0f);
    RayTracer::Shared::Vec3 right = _direction.cross(up);
    if (right.length() < 1e-6) {
        up = RayTracer::Shared::Vec3(0.0f, 0.0f, 1.0f);
        right = _direction.cross(up);
    }
    right.normalize();
    return right;
}

RayTracer::Shared::Vec3 RayTracer::Plugins::Cameras::ACamera::getLeftVector() const
{
    return getRightVector() * -1.0f;
}