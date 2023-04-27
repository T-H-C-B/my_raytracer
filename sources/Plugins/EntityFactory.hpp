//
// Created by Clément Lagasse on 27/04/2023.
//

#ifndef RAYTRACING_ENTITYFACTORY_HPP
#define RAYTRACING_ENTITYFACTORY_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "IEntity.hpp"

namespace RayTracer {
    namespace Plugins {

        class EntityFactory {
        public:
            EntityFactory() = default;
            ~EntityFactory() = default;

            void registerEntity(const std::string &type, std::function<std::unique_ptr<RayTracer::Core::IEntity>(const RayTracer::Shared::Vec3 &, const RayTracer::Shared::Vec3 &)> factoryMethod);
            std::unique_ptr<RayTracer::Core::IEntity> createEntity(const std::string &type, const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation) const;
        private:
            std::unordered_map<std::string, std::function<std::unique_ptr<RayTracer::Core::IEntity>(const RayTracer::Shared::Vec3 &, const RayTracer::Shared::Vec3 &)>> _factories;
        };

    } // RayTracer
} // Plugins

#endif //RAYTRACING_ENTITYFACTORY_HPP
