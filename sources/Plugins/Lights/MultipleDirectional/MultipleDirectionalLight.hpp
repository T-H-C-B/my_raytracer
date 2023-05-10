//
// Created by Clément Lagasse on 09/05/2023.
//

#pragma once

#include <memory>
#include <vector>
#include "ALight.hpp"
#include "DirectionalLight.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Lights {

            class MultipleDirectionalLight : public RayTracer::Plugins::Lights::ALight {
            public:
                MultipleDirectionalLight(const RayTracer::Shared::Vec3 &position, float intensity, const RayTracer::Shared::Vec3 &color);

                void addLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color);

                bool inView(const RayTracer::Shared::Vec3 &point) const;

                int getNbLights() const { return lights.size();}

                virtual ~MultipleDirectionalLight() = default;

            private:
                std::vector<std::unique_ptr<RayTracer::Plugins::Lights::DirectionalLight>> lights;
            };
        }
    } // namespace Plugins
} // namespace RayTracer
