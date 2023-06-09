//
// Created by Theophilus Homawoo on 04/05/2023.
//

#pragma once

#include "IDecorator.hpp"
#include <vector>
#include <unordered_map>

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            class FlatColor : public RayTracer::Plugins::Decorators::IDecorator {
            public:
                FlatColor(const Shared::Vec3 &color, float absorption, float specularConstant, float shininess);
                ~FlatColor() override = default;
                void computeColor(RayTracer::Shared::Intersection &intersection,
                                  const RayTracer::Shared::Ray &ray,
                                  RayTracer::Shared::Vec3 &baseColor,
                                  std::unordered_map<RayTracer::Core::EntityType,
                                          std::vector<RayTracer::Core::IEntity *>>,
                                  RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) override;
            private:
                Shared::Vec3 _color;
                float _absorption;
                float _specularConstant;
                float _shininess;

            };

        } // RayTracer
    } // Plugins
} // Decorator
