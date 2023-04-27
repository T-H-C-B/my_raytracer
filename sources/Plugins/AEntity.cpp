//
// Created by Clément Lagasse on 24/04/2023.
//

#include "AEntity.hpp"

RayTracer::Core::AEntity::AEntity(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation)
: _position(position), _rotation(rotation)
{
}

void RayTracer::Core::AEntity::translate(const RayTracer::Shared::Vec3 &translation)
{
    _position += translation;
}

void RayTracer::Core::AEntity::rotate(const RayTracer::Shared::Vec3 &rotation)
{
    _rotation += rotation;
}


