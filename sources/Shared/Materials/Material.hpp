//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <vector>
#include "IDecorator.hpp"
#include "unordered_map"
#include "Intersection.hpp"
#include "Vec3.hpp"
#include "IEntity.hpp"

namespace RayTracer {
    namespace Shared {

        class Material {
        public:
            Material() = default;
            ~Material() = default;
            void addDecorator(RayTracer::Plugins::Decorators::IDecorator *decorator);
            Vec3 computeColor(RayTracer::Shared::Intersection &intersection, Ray const &ray, std::unordered_map<Core::EntityType, std::vector<RayTracer::Core::IEntity *>> &entities);


        private:
            std::vector<RayTracer::Plugins::Decorators::IDecorator *> _decorators;
        };

    } // RayTracer
} // Shared
