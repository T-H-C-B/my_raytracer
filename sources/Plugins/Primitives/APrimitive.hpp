//
// Created by Theophilus Homawoo on 19/04/2023.
//

#ifndef RAYTRACING_APRIMITIVE_HPP
#define RAYTRACING_APRIMITIVE_HPP

#include "IEntity.hpp"
#include "IPrimitive.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {
        class APrimitive : public RayTracer::Core::IEntity {
            public:
                APrimitive() = default;

                virtual ~APrimitive() = default;

                RayTracer::Core::EntityType getType() const override { return RayTracer::Core::EntityType::Primitive; }
            };
        }
    }
}

#endif //RAYTRACING_APRIMITIVE_HPP
