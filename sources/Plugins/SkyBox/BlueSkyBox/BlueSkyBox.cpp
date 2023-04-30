//
// Created by Bartosz on 4/30/23.
//


#include "BlueSkyBox.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            RayTracer::Shared::Vec3 BlueSkyBox::getColor(const RayTracer::Shared::Ray &ray) const {
                return RayTracer::Shared::Vec3(0.0f, 0.0f, 1.0f);
            }
        }
    } // RayTracer
} // Plugins
