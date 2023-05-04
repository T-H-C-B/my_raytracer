/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#pragma once
#include <optional>
#include "AEntity.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {

            class Cylinder : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Cylinder(const RayTracer::Shared::Vec3& position, float radius);
                ~Cylinder() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                float _radius{};
                RayTracer::Shared::Vec3 _color;
            };
        } // Primitives
    } // Plugins
} // Raytracer
