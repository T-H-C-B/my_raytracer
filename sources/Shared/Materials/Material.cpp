//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Material.hpp"

//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Material.hpp"

namespace RayTracer {
    namespace Shared {

        void Material::addDecorator(IDecorator *decorator) {
            _decorators.push_back(decorator);
        }

        void Material::computeColor(Intersection &intersection, Ray const &ray, std::unordered_map<EntityType, std::vector<IEntity *>> &entities) {
            for (auto &decorator : _decorators) {
                decorator->computeColor(intersection, ray, entities);
            }
        }

    } // namespace Shared
} // namespace RayTracer

