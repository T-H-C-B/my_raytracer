//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ICAMERA_HPP
#define MY_RAYTRACER_ICAMERA_HPP

#include "IEntity.hpp"

namespace RayTracer {
    namespace Entities {

        class ICamera : public IEntity {
            public:

                virtual void setFov(float fov) = 0;
                virtual std::vector<std::vector<Ray>> calculateRays() const = 0;
                virtual ~ICamera() = default;
        };

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ICAMERA_HPP
