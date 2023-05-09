// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include "SettingWrapper.hpp"
#include <string>
#include <unordered_map>
#include <functional>
#include "CustomError.hpp"


namespace RayTracer {
    namespace Core {

        template <typename T>
        class Factory {
        public:

            Factory() = default;
            ~Factory() = default;
            void registerPlugin(const std::string &name, std::function<T *(const RayTracer::Shared::SettingWrapper &)> func);
            T *create(const std::string &name, const RayTracer::Shared::SettingWrapper &config);
        private:
            std::unordered_map<std::string, std::function<T *(const RayTracer::Shared::SettingWrapper &)>> _factory;
        };

        template <typename T>
        void Factory<T>::registerPlugin(const std::string &name, std::function<T *(const RayTracer::Shared::SettingWrapper &)> func) {
            _factory[name] = func;
        }

        template <typename T>
        T *Factory<T>::create(const std::string &name, const RayTracer::Shared::SettingWrapper &config) {
            auto it = _factory.find(name);
            if (it != _factory.end()) {
                return it->second(config);
            }
            throw RayTracer::Shared::CustomError("Factory: Plugin not found");
        }

    }
}
