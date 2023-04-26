// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_FACTORY_HPP
#define MY_RAYTRACER_FACTORY_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "IEntity.hpp"

namespace RayTracer {
    namespace Core {

        class Factory {
        public:
            Factory() = default;
            ~Factory() = default;

            void registerPlugin(const std::string &name, std::function<RayTracer::Core::IEntity *()> func);
            RayTracer::Core::IEntity *create(const std::string &name);

            Factory(const Factory &other) = delete;
            Factory &operator=(const Factory &other) = delete;

            Factory(Factory &&other) = delete;
            Factory &operator=(Factory &&other) = delete;
        private:
            std::unordered_map<std::string, std::function<RayTracer::Core::IEntity *()>> _factory;
        };

    } // namespace Core
} // namespace RayTracer

#endif //MY_RAYTRACER_IFACTORY_HPP
