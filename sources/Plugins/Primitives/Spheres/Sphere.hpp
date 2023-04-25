//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include "IEntity.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {

            class Sphere : public IEntity {
            public:
                Sphere() = default;
                Sphere(const Vec3& center, float radius, const Vec3& color);
                ~Sphere() override = default;

                void translate(const Vec3& translation) override;
                EntityType getType() const override;
                void rotate(const Vec3& rotation) override;
                void scale(float scale) override;
                bool intersect(const Ray& ray, float& t) const override;

            private:
                Vec3 center;
                float radius{};
                Vec3 color;
            };

        } // Primitives
    } // Plugins
} // Raytracer


#endif //RAYTRACING_SPHERE_HPP
