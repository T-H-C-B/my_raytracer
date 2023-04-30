//
// Created by Theophilus Homawoo on 30/04/2023.
//

#ifndef RAYTRACING_PLANE_HPP
#define RAYTRACING_PLANE_HPP

#include <optional>
#include <memory>
#include <string>
#include "AEntity.hpp"
#include "IEntity.hpp"
#include "../APrimitive.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {

            class Plane : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Plane(const std::string& axis, float position, const RayTracer::Shared::Vec3& color);
                ~Plane() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                std::string axis;
                float position;
                RayTracer::Shared::Vec3 color;
            };

        } // Primitives
    } // Plugins
} // Raytracer

#endif //RAYTRACING_PLANE_HPP