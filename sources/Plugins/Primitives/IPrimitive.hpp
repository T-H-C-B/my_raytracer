//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_IPRIMITIVE_HPP
#define MY_RAYTRACER_IPRIMITIVE_HPP

namespace RayTracer {
    namespace Plugins {

        namespace Primitives {
            class IPrimitive {

                virtual bool intersect(const Ray& ray, float& t) const = 0;
                virtual void scale(float scale) = 0;
            };
        } // Primitives

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_IPRIMITIVE_HPP
