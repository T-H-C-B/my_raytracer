//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
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

