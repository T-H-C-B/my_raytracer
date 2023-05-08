//
// Created by Theophilus Homawoo on 14/04/2023.
//

#pragma once

#include <memory>
#include "Vec3.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {
            class APrimitive;
        }
    }
    namespace Shared {
        struct Intersection {
            bool hit;
            float t;
            Vec3 point;
            Vec3 normal;
            Plugins::Primitives::APrimitive *primitive;

            Intersection() : hit(false), t(0.0f), point(), normal() {}
        };
    }
}


