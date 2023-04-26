//
// Created by Theophilus Homawoo on 19/04/2023.
//

#ifndef RAYTRACING_APRIMITIVE_HPP
#define RAYTRACING_APRIMITIVE_HPP

#include "IEntity.hpp"
#

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {
            class APrimitive : public IEntity {
            public:
                APrimitive() = default;

                virtual ~APrimitive() = default;

                EntityType getType() const override { return EntityType::Primitive; }
            };
        }
    }
}

#endif //RAYTRACING_APRIMITIVE_HPP
