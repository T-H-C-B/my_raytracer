//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Material.hpp"

namespace RayTracer {
    namespace Shared {

        void Material::addDecorator(RayTracer::Plugins::Decorators::IDecorator *decorator) {
            _decorators.push_back(decorator);
        }

        Vec3 Material::computeColor(Intersection &intersection, const Ray &ray,
                                    std::unordered_map<Core::EntityType, std::vector<RayTracer::Core::IEntity *>> &entities) {
            Vec3 color = Vec3();
            for (auto &decorator : _decorators) {
                decorator->computeColor(intersection, ray, color, entities);
            }
            return color;
        }
    } // RayTracer
} // Shared