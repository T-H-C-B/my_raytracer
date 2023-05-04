//
// Created by Theophilus Homawoo on 28/04/2023.
//

#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <filesystem>
#include <memory>
#include "FactoryTemplate.hpp"
#include "IEntity.hpp"
#include "IDecorator.hpp"
#include "ISkyBox.hpp"
#include "IGraphModule.hpp"
#include "PluginType.hpp"
#include "DynamicLibrary.hpp"
#include <vector>

namespace fs = std::filesystem;

namespace RayTracer {
    namespace Core {
        using FactoryVariant = std::variant<Factory<RayTracer::Core::IEntity> *,
                Factory<RayTracer::Plugins::Decorators::IDecorator> *,
                Factory<RayTracer::Plugins::Skyboxes::ISkyBox> *,
                Factory<RayTracer::Plugins::Graphics::IGraphModule> *>;

        class PluginLoader {
        public:
            PluginLoader(Factory<RayTracer::Core::IEntity> &entityFactory,
                         Factory<RayTracer::Plugins::Decorators::IDecorator> &decoratorFactory,
                         Factory<RayTracer::Plugins::Skyboxes::ISkyBox> &skyboxFactory,
                         Factory<RayTracer::Plugins::Graphics::IGraphModule> &graphModuleFactory);
            ~PluginLoader();

            std::shared_ptr<DynamicLibrary> loadPlugin(const std::string &path);
            void loadLibraries(const std::string &directory);
            std::unordered_map<std::string, RayTracer::Plugins::PluginType> getLibraries() const;
            std::unordered_map<std::string, FactoryVariant> getFactories() const;
        private:
            std::unordered_map<std::string, FactoryVariant> _factories;
            std::unordered_map<std::string, RayTracer::Plugins::PluginType> _libraries;

            Factory<RayTracer::Core::IEntity> &entityFactory;
            Factory<RayTracer::Plugins::Decorators::IDecorator> &decoratorFactory;
            Factory<RayTracer::Plugins::Skyboxes::ISkyBox> &skyboxFactory;
            Factory<RayTracer::Plugins::Graphics::IGraphModule> &graphModuleFactory;
            std::vector<std::shared_ptr<DynamicLibrary>> _loadedLibraries;
        };

    } // RayTracer
} // Core

