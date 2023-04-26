//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_BlueSkyBox_HPP
#define MY_RAYTRACER_BlueSkyBox_HPP

#include "ISkyBox.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class BlueSkyBox : public ISkyBox {
            public:
                virtual ~BlueSkyBox() = default;

                virtual Vec3f getColor(const Ray &ray) const = 0;
            };
        }
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_BlueSkyBox_HPP
