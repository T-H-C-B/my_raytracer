//
// Created by Clément Lagasse on 02/05/2023.
//

#include "DirectionMethod.hpp"

RayTracer::Shared::Vec3 &RayTracer::Shared::DirectionMethod::getDirectionByRotation(const RayTracer::Shared::Vec3 &rotation)
{
    float pitchRadians = rotation.x * (M_PI / 180.0f);
    float yawRadians = rotation.y * (M_PI / 180.0f);

    float x = cosf(yawRadians) * cosf(pitchRadians);
    float y = sinf(pitchRadians);
    float z = sinf(yawRadians) * cosf(pitchRadians);

    RayTracer::Shared::Vec3* direction = new RayTracer::Shared::Vec3(x, y, z);

    return *direction;
}