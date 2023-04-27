//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ILIGHT_HPP
#define MY_RAYTRACER_ILIGHT_HPP

#include "IEntity.hpp"
#include "Vec3.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Lights {
            class ILight : public RayTracer::Core::IEntity {

            public:

                virtual float getIntensity() const = 0;

                virtual RayTracer::Shared::Vec3 &getPosition() const = 0;

                virtual bool inView(const RayTracer::Shared::Vec3 &point) const = 0;


                virtual ~ILight() = default;
            };
        }

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ILIGHT_HPP
