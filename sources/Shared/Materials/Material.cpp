//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Material.hpp"

namespace RayTracer {
    namespace Shared {
        void Material::addDecorator(IDecorator *decorator) {
            _decorators.push_back(decorator);
        }

        Vec3 Material::computeColor(Intersection &intersection, const Ray &ray,
                                    std::unordered_map<EntityType, type, std::vector<IEntity *>> &entities) {
            for (auto &decorator : _decorators) {
                decorator->computeColor(intersection, ray, Vec3(0, 0, 0));
            }
        }
    } // RayTracer
} // Shared