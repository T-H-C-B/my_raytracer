//
// Created by Theophilus Homawoo on 04/05/2023.
//

#include "FlatColor.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            FlatColor::FlatColor(const RayTracer::Shared::Vec3 &color) : _color(color) {}

            void FlatColor::computeColor(RayTracer::Shared::Intersection &intersection,
                                                            RayTracer::Shared::Ray const &ray,
                                                            RayTracer::Shared::Vec3 &baseColor,
                                                            std::unordered_map<RayTracer::Core::EntityType,
                                                            std::vector <RayTracer::Core::IEntity * >>,
                                                            RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
                baseColor = _color;
            }
        } // RayTracer
    } // Plugins
} // Decorator