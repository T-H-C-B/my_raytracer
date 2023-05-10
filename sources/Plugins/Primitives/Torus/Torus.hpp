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
                double solveQuartic(double coefficients[5], double roots[4]) const;
                int solveCubic(double coefficients[4], double roots[3]) const;
                int solveQuadratic(double coefficients[3], double roots[2]) const;

                float _majorRadius;
                float _minorRadius;
                RayTracer::Shared::Vec3 _rotation;

            };
        } // Primitives
    } // Plugins
} // Raytracer
