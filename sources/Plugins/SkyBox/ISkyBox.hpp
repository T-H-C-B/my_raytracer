//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ISKYBOX_HPP
#define MY_RAYTRACER_ISKYBOX_HPP

#include "IEntity.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {

        class ISkyBox : public IEntity {
        public:
            virtual ~ISkyBox() = default;

            virtual Vec3f getColor(const Ray &ray) const = 0;
        };

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ISKYBOX_HPP
