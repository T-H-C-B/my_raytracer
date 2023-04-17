//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_IENTITY_HPP
#define RAYTRACING_IENTITY_HPP

#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"

enum EntityType {
    Primitive,
    Light,
    Camera
};

class IEntity {
public:
    IEntity() = default;
    virtual ~IEntity() = default;

    virtual void translate(const Vec3& translation) = 0;
    virtual void rotate(const Vec3& rotation) = 0;
    virtual void scale(float scale) = 0;
    virtual bool intersect(const Ray& ray, float& t) const = 0;

    virtual EntityType getType() const = 0;
};



#endif //RAYTRACING_IENTITY_HPP
