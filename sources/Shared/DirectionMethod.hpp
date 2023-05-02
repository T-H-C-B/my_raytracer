//
// Created by Clément Lagasse on 02/05/2023.
//

#pragma once

#include <cmath>
#include "Vec3.hpp"

namespace RayTracer {
    namespace Shared {
        class DirectionMethod {
        public:

            static RayTracer::Shared::Vec3 &getDirectionByRotation(const RayTracer::Shared::Vec3 &rotation);
        };
    }
} // RayTracer
