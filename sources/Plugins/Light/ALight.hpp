//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ALIGHT_HPP
#define MY_RAYTRACER_ALIGHT_HPP

#include "AEntity.hpp"
#include "ILight.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Lights {
            class ALight : public RayTracer::Plugins::Lights::ILight , public RayTracer::Core::AEntity {
            public:
                ALight() = default;

                float getIntensity() const;

                RayTracer::Shared::Vec3 &getPosition() const;

                virtual ~ALight() = default;

            private:
                float _intensity;
            };
        }
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ALIGHT_HPP
