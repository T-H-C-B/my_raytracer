//
// Created by Clément Lagasse on 02/05/2023.
//

#pragma once

#include "Vec3.hpp"
#include "ALight.hpp"

namespace RayTracer {

    namespace Plugins {

        namespace Lights {

            class DirectionalLight : public RayTracer::Plugins::Lights::ALight {
            public:
                DirectionalLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color);

                bool inView(const RayTracer::Shared::Vec3 &point) const override;

                virtual ~DirectionalLight() = default;

            };
        }
    } // RayTracer
} // RayTracer


