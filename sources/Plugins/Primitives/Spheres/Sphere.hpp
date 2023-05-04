//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include <optional>
#include "AEntity.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {

            class Sphere : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Sphere(const RayTracer::Shared::Vec3& center, float radius, RayTracer::Shared::Material *material);
                ~Sphere() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>>  intersect(const RayTracer::Shared::Ray&ray, float& t) const override;

            private:
                float radius{};
            };

        } // Primitives
    } // Plugins
} // Raytracer


#endif //RAYTRACING_SPHERE_HPP
