//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_IDECORATOR_HPP
#define MY_RAYTRACER_IDECORATOR_HPP

#include <unordered_map>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "IEntity.hpp"
#include "Intersection.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            class IDecorator {
            public:
                virtual ~IDecorator() = default;

                virtual void computeColor(RayTracer::Shared::Intersection &intersection,
                                          RayTracer::Shared::Ray const &ray,
                                          RayTracer::Shared::Vec3 &baseColor,
                                          std::unordered_map<RayTracer::Core::EntityType,
                                          std::vector <RayTracer::Core::IEntity * >>) = 0;
            };
        }
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_IDECORATOR_HPP
