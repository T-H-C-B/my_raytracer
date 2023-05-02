//
// Created by Clément Lagasse on 24/04/2023.
//

#include "DirectionMethod.hpp"
#include "AEntity.hpp"

RayTracer::Core::AEntity::AEntity(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation)
: _position(position), _rotation(rotation), _direction(RayTracer::Shared::DirectionMethod::getDirectionByRotation(rotation))
{
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

    _direction = RayTracer::Shared::DirectionMethod::getDirectionByRotation(_rotation);
    _direction.normalize();
}


