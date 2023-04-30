//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include "IEntity.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class ISkyBox {
            public:
                virtual ~ISkyBox() = default;

                virtual void rotate(const RayTracer::Shared::Vec3 &rotation) = 0;
                virtual RayTracer::Shared::Vec3 getColor(const RayTracer::Shared::Ray &ray) const = 0;
            };
        }
    } // RayTracer
} // Plugins

