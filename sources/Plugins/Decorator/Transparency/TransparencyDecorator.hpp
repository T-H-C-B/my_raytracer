//
// Created by Theophilus Homawoo on 08/05/2023.
//

#pragma once

#include "IDecorator.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {

            class TransparentDecorator : public IDecorator {
            public:
                TransparentDecorator(float opacity, float indexOfRefraction);

                void computeColor(RayTracer::Shared::Intersection &intersection,
                                  RayTracer::Shared::Ray const &ray,
                                  RayTracer::Shared::Vec3 &baseColor,
                                  std::unordered_map<RayTracer::Core::EntityType,
                                  std::vector <RayTracer::Core::IEntity * >> entities,
                                  RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) override;

            private:
                float _opacity;
                float _indexOfRefraction;
            };


        } // RayTracer
    } // Plugins
} // Decorators
