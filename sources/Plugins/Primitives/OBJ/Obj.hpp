/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#pragma once

#include <optional>
#include <algorithm>
#include "AEntity.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"
#include "Vec2.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Primitives {

            struct Face {
                int v1, v2, v3;
                int uv1, uv2, uv3;
                int n1, n2, n3;
            };

            class Obj : public RayTracer::Plugins::Primitives::APrimitive {
            public:
                Obj(const RayTracer::Shared::Vec3& position, const RayTracer::Shared::Vec3& rotation, const std::string &path, float scale);
                ~Obj() override = default;

                void scale(float scale) override;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> intersect(const RayTracer::Shared::Ray& ray, float& t) const override;

            private:
                void loadObjFile(const std::string &path);
                bool rayTriangleIntersection(const RayTracer::Shared::Ray& ray, const Face& face, float& t) const;

                std::vector<RayTracer::Shared::Vec3> _vertices;
                std::vector<RayTracer::Shared::Vec3> _normals;
                std::vector<RayTracer::Shared::Vec2> _uvs;
                std::vector<Face> _faces;
                float _scale;
            };
        } // Primitives
    } // Plugins
} // Raytracer
