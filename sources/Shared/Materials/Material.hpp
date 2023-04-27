//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_MATERIAL_HPP
#define MY_RAYTRACER_MATERIAL_HPP

#include <vector>
#include "IDecorator.hpp"
#include "Intersection.hpp"
#include "Vec3.hpp"

namespace RayTracer {
    namespace Shared {

        class Material {
        public:
            Material() = default;
            ~Material() = default;
            void addDecorator(RayTracer::Plugins::Decorators::IDecorator *decorator);
            Vec3 computeColor(RayTracer::Shared::Intersection &intersection, Ray const &ray, std::unordered_map<EntityType type, std::vector<IEntity *>> &entities);

        private:
            std::vector<RayTracer::Plugins::Decorators::IDecorator *> _decorators;
        };

    } // RayTracer
} // Shared

#endif //MY_RAYTRACER_MATERIAL_HPP
