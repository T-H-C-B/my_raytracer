//
// Created by Theophilus Homawoo on 08/05/2023.
//

#pragma once

#include "IDecorator.hpp"
#include "Material.hpp"
#include "CustomError.hpp"
#include "APrimitive.hpp"
#include "Vec3.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {

            class ReflectionDecorator : public IDecorator {
            public:
                ReflectionDecorator(float reflectivity);

                void computeColor(RayTracer::Shared::Intersection &intersection,
                                  RayTracer::Shared::Ray const &ray,
                                  RayTracer::Shared::Vec3 &baseColor,
                                  std::unordered_map<RayTracer::Core::EntityType,
                                  std::vector <RayTracer::Core::IEntity * >> entities,
                                  RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) override;

            private:
                float _reflectivity;
            };

        } // RayTracer
    } // Plugins
} // Decorators

