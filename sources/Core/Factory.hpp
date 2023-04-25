//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_FACTORY_HPP
#define MY_RAYTRACER_FACTORY_HPP

#include <unordered_map>

class RayTracer::Entities::IEntity;

namespace RayTracer {
    namespace Core {

        class Factory {
        public:
            Factory() = default;
            ~Factory() = default;

            void registerPlugin(const std::string &name, std::function<IEntity *()> func);
            IEntity *create(const std::string &name);

            Factory(const Factory &other) = delete;
            Factory &operator=(const Factory &other) = delete;

            Factory(Factory &&other) = delete;
            Factory &operator=(Factory &&other) = delete;
        private:
            std::unordered_map<std::string, std::function<IEntity *()>> _factory;
        };

    } // RayTracer
} // Core

#endif //MY_RAYTRACER_IFACTORY_HPP
