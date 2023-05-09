#pragma once
#include <optional>
#include <memory>
#include <string>
#include "AEntity.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"
#include "Material.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {

            class Plane : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Plane(const RayTracer::Shared::Vec3 &axis, const RayTracer::Shared::Vec3 &position);
                ~Plane() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                RayTracer::Shared::Vec3 _axis;
                RayTracer::Shared::Vec3 _position;
            };

        } // Primitives
    } // Plugins
} // Raytracer
