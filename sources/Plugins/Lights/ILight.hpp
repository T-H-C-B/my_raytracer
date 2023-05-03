//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include "IEntity.hpp"
#include "Vec3.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Lights {
            class ILight {

            public:

                virtual float getIntensity() const = 0;

                virtual RayTracer::Shared::Vec3 &getColor() = 0;

                virtual RayTracer::Shared::Vec3 &getPosition() = 0;

                virtual RayTracer::Shared::Vec3 &getDirection() = 0;

                virtual bool inView(const RayTracer::Shared::Vec3 &point) const = 0;


                virtual ~ILight() = default;
            };
        }

    } // RayTracer
} // Plugins

