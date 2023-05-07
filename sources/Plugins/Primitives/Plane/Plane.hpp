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
                Plane(const std::string& axis, float position);
                ~Plane() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                std::string _axis;
                float _position;
            };

        } // Primitives
    } // Plugins
} // Raytracer
