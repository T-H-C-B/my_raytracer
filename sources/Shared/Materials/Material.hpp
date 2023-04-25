//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_MATERIAL_HPP
#define MY_RAYTRACER_MATERIAL_HPP

#include <vector>
#include "IDecorator.hpp"

namespace RayTracer {
    namespace Shared {

        class Material {
        public:
            Material() = default;
            ~Material() = default;
            void addDecorator(IDecorator *decorator);
            void computeColor(Intersection &intersection, Ray const &ray, std::unordered_map<EntityType type, std::vector<IEntity *>> &entities);

        private:
            std::veector<IDecorator *> _decorators;
        };

    } // RayTracer
} // Shared

#endif //MY_RAYTRACER_MATERIAL_HPP
