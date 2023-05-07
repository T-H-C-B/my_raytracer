//
// Created by Theophilus Homawoo on 30/04/2023.
//

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
                Plane(RayTracer::Shared::Vec3 &position, RayTracer::Shared::Vec3 &normal);
                ~Plane() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                RayTracer::Shared::Vec3 _normal;
            };

        } // Primitives
    } // Plugins
} // Raytracer
