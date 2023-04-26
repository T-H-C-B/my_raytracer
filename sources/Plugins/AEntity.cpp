//
// Created by Clément Lagasse on 24/04/2023.
//

#include "AEntity.hpp"

RayTracer::Core::AEntity::AEntity(Vec3 const &position, Vec3 const &rotation)
: position(position), rotation(rotation)
{
}

void RayTracer::Core::AEntity::translate(const Vec3 &translation)
{
    _position += translation;
}

void RayTracer::Core::AEntity::rotate(const Vec3 &rotation)
{
    _rotation += rotation;
}


