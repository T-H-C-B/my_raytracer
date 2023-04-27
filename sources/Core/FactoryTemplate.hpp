// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_FACTORY_HPP
#define MY_RAYTRACER_FACTORY_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <libconfig.h++>

namespace RayTracer {
    namespace Core {

        template <typename T>
        class Factory {
        public:
            void registerPlugin(const std::string &name, std::function<T *(const libconfig::Setting &)> func);
            T *create(const std::string &name, const libconfig::Setting &config);
        private:
            std::unordered_map<std::string, std::function<T *(const libconfig::Setting &)>> _factory;
        };

        template <typename T>
        void Factory<T>::registerPlugin(const std::string &name, std::function<T *(const libconfig::Setting &)> func) {
            _factory[name] = func;
        }

        template <typename T>
        T *Factory<T>::create(const std::string &name, const libconfig::Setting &config) {
            auto it = _factory.find(name);
            if (it != _factory.end()) {
                return it->second(config);
            }
            return nullptr;
        }

    } // namespace Core
} // namespace RayTracer

#endif //MY_RAYTRACER_FACTORY_HPP
