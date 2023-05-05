//
// Created by Clément Lagasse on 24/04/2023.
//

#include "AEntity.hpp"

RayTracer::Core::AEntity::AEntity(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation)
: _position(position), _rotation(rotation), _direction(0.0f, 0.0f, 0.0f)
{
    RayTracer::Core::AEntity::rotate(rotation);
}

void RayTracer::Core::AEntity::translate(const RayTracer::Shared::Vec3 &translation)
{
    _position += translation;
}

void RayTracer::Core::AEntity::rotate(const RayTracer::Shared::Vec3 &rotation)
{
    _rotation += rotation;

    _rotation.x = fmod(_rotation.x, 360.0f);
    _rotation.y = fmod(_rotation.y, 360.0f);
    _rotation.z = fmod(_rotation.z, 360.0f);

    float pitchRadians = _rotation.x * (M_PI / 180.0f);
    float yawRadians = _rotation.y * (M_PI / 180.0f);
    float x = cosf(yawRadians) * cosf(pitchRadians);
    float y = sinf(pitchRadians);
    float z = sinf(yawRadians) * cosf(pitchRadians);
    _direction.x = x;
    _direction.y = y;
    _direction.z = z;

    _direction = _direction.normalize();
}


