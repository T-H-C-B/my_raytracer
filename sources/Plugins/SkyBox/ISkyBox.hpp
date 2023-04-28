//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ISKYBOX_HPP
#define MY_RAYTRACER_ISKYBOX_HPP

#include "IEntity.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class ISkyBox : public RayTracer::Core::IEntity {
            public:
                virtual ~ISkyBox() = default;

                virtual Shared::Vec3 getColor(const Shared::Ray &ray) const = 0;
            };
        }
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ISKYBOX_HPP
