//
// Created by Clément Lagasse on 24/04/2023.
//

#include "AEntity.hpp"

RayTracer::Entities::AEntity::AEntity(Vec3 const &position, Vec3 const &rotation)
: position(position), rotation(rotation)
{
}

void RayTracer::Entities::AEntity::translate(const Vec3 &translation)
{
    _position += translation;
}

void RayTracer::Entities::AEntity::rotate(const Vec3 &rotation)
{
    _rotation += rotation;
}


