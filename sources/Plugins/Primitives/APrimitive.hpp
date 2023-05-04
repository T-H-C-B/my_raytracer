//
// Created by Theophilus Homawoo on 19/04/2023.
//

#ifndef RAYTRACING_APRIMITIVE_HPP
#define RAYTRACING_APRIMITIVE_HPP

#include "Vec3.hpp"
#include "IEntity.hpp"
#include "IPrimitive.hpp"
#include "Material.hpp"
#include "AEntity.hpp"
#include "Material.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {
        class APrimitive : public RayTracer::Core::AEntity, public RayTracer::Plugins::Primitives::IPrimitive {
            public:
                APrimitive(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, RayTracer::Shared::Material &material)
                : RayTracer::Core::AEntity(position, rotation), _material(material){};

                virtual ~APrimitive() = default;

                RayTracer::Core::EntityType getType() const override { return RayTracer::Core::EntityType::Primitive; }
                RayTracer::Shared::Material &getMaterial() const override { return _material; }
            private:
                RayTracer::Shared::Material &_material;
            };
        }
    }
}

#endif //RAYTRACING_APRIMITIVE_HPP
