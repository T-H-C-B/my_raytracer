//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Material.hpp"

namespace RayTracer {
    namespace Shared {
        void Material::addDecorator(IDecorator *decorator) {
            return;
        }

        Vec3 Material::computeColor(Intersection &intersection, const Ray &ray,
                                    std::unordered_map<EntityType, type, std::vector<IEntity *>> &entities) {
            return Vec3(0, 0, 0);
        }
    } // RayTracer
} // Shared