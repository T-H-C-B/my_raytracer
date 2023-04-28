//
// Created by Theophilus Homawoo on 19/04/2023.
//

#ifndef RAYTRACING_APRIMITIVE_HPP
#define RAYTRACING_APRIMITIVE_HPP

#include "Vec3.hpp"
#include "IEntity.hpp"
#include "IPrimitive.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {
        class APrimitive : public RayTracer::Core::AEntity, public RayTracer::Plugins::Primitives::IPrimitive {
            public:
                APrimitive(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation)
                : RayTracer::Core::AEntity(position, rotation){};

                virtual ~APrimitive() = default;

                RayTracer::Core::EntityType getType() const override { return RayTracer::Core::EntityType::PRIMITIVE; }
            };
        }
    }
}

#endif //RAYTRACING_APRIMITIVE_HPP
