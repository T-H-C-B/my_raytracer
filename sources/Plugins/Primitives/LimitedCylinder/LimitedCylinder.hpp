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
            class LimitedCylinder : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                LimitedCylinder(const RayTracer::Shared::Vec3& position, float radius, const RayTracer::Shared::Vec3& rotate, int height);
                ~LimitedCylinder() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                RayTracer::Shared::Vec3 cylNormal(const RayTracer::Shared::Vec3 &p, const RayTracer::Shared::Vec3 &a, const RayTracer::Shared::Vec3 &b, float ra) const;
                std::optional<float> cylIntersect(const RayTracer::Shared::Ray &ray, const RayTracer::Shared::Vec3 &a, const RayTracer::Shared::Vec3 &b, float ra) const;
                float _radius;
                int _height;
                RayTracer::Shared::Vec3 _rotation;
            };
        } // Primitives
    } // Plugins
} // Raytracer
