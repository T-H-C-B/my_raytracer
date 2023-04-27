//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_INTERSECTION_HPP
    #define RAYTRACING_INTERSECTION_HPP

#include <memory>
#include "Vec3.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Shared {
        struct Intersection {
            bool hit;
            float t;
            Vec3 point;
            Vec3 normal;

            Intersection() : hit(false), t(0.0f), point(), normal() {}
        };
    }
}


#endif //RAYTRACING_INTERSECTION_HPP
