//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_IMATERIAL_HPP
#define RAYTRACING_IMATERIAL_HPP

#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"

class IMaterial {
public:
    virtual ~IMaterial() = default;

    virtual bool scatter(const Ray& rayIn, const Intersection& intersection,
                         Vec3& attenuation, Ray& scattered) const = 0;
};


#endif //RAYTRACING_IMATERIAL_HPP
