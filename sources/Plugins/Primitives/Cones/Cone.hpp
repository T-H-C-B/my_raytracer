/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cone
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
            class Cone : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Cone(const RayTracer::Shared::Vec3& position, float radius, const RayTracer::Shared::Vec3& rotation, int height);

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersectBase(const RayTracer::Shared::Ray& ray, float& t) const;
                float _radius;
                int _height;
                RayTracer::Shared::Vec3 _rotation;
            };
        } // Primitives
    } // Plugins
} // Raytracer

