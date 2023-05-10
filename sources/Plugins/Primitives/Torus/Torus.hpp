/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Torus
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
            class Torus : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Torus(const RayTracer::Shared::Vec3& position, float majorRadius, float minorRadius, const RayTracer::Shared::Vec3& rotation);

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                RayTracer::Shared::Vec3 torNormal(const RayTracer::Shared::Vec3& pos) const;
                float torIntersect(const RayTracer::Shared::Ray& ray) const;
                float _majorRadius;
                float _minorRadius;
                RayTracer::Shared::Vec3 _rotation;

            };
        } // Primitives
    } // Plugins
} // Raytracer
