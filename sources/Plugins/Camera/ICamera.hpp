//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ICAMERA_HPP
#define MY_RAYTRACER_ICAMERA_HPP

#include <vector>
#include "IEntity.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Cameras {
            class ICamera {
            public:

                virtual void setFov(float fov) = 0;

                virtual std::vector<std::vector<RayTracer::Shared::Ray>> calculateRays() = 0;

                virtual Shared::Vec3 &getDirection() = 0;

                virtual Shared::Vec3 getRightVector() const = 0;
                virtual Shared::Vec3 getLeftVector() const = 0;

                virtual ~ICamera() = default;
            };
        }

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ICAMERA_HPP
