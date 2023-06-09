//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_IENTITY_HPP
#define RAYTRACING_IENTITY_HPP

#include "Vec3.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Core {
        enum EntityType {
            Primitive,
            Light,
            Camera,
        };

        class IEntity {
            public:
                IEntity() = default;
                virtual ~IEntity() = default;

                virtual void translate(const RayTracer::Shared::Vec3& translation) = 0;
                virtual void rotate(const RayTracer::Shared::Vec3& rotation) = 0;

                virtual EntityType getType() const = 0;
        };
    }
}

#endif //RAYTRACING_IENTITY_HPP
