//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_IDECORATOR_HPP
#define MY_RAYTRACER_IDECORATOR_HPP

#include "Vec3.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "IEntity.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"



namespace RayTracer {
    namespace Plugins {

        class IDecorator {
        public:
            virtual ~IDecorator() = default;
            virtual void computeColor(Intersection &intersection, Ray const &ray, Vec3 baseColor, std::unordered_map<EntityType type, std::vector<IEntity *>> &entities) = 0;
        };

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_IDECORATOR_HPP
