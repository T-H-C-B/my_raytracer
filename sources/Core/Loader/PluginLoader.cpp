//
// Created by Theophilus Homawoo on 28/04/2023.
//

#include "PluginLoader.hpp"
#include "CustomError.hpp"
#include <functional>
#include <iostream>
#include <libconfig.h++>

namespace RayTracer {
    namespace Core {


        using CreateEntityFunc = RayTracer::Core::IEntity* (*)(const libconfig::Setting&);
        using CreateDecoratorFunc = RayTracer::Plugins::Decorators::IDecorator* (*)(const libconfig::Setting&);
        using CreateSkyboxFunc = RayTracer::Plugins::Skyboxes::ISkyBox* (*)(const libconfig::Setting&);
        using CreateGraphModuleFunc = RayTracer::Plugins::Graphics::IGraphModule* (*)(const libconfig::Setting&);

        PluginLoader::PluginLoader(Factory<RayTracer::Core::IEntity> &entityFactory,
                                   Factory<RayTracer::Plugins::Decorators::IDecorator> &decoratorFactory,
                                   Factory<RayTracer::Plugins::Skyboxes::ISkyBox> &skyboxFactory,
                                   Factory<RayTracer::Plugins::Graphics::IGraphModule> &graphModuleFactory) : entityFactory(entityFactory),
                                                                                                    decoratorFactory(decoratorFactory),
                                                                                                    skyboxFactory(skyboxFactory),
                                                                                                    graphModuleFactory(graphModuleFactory) {
        }

        PluginLoader::~PluginLoader() {
        }

        std::shared_ptr<DynamicLibrary> PluginLoader::loadPlugin(const std::string &path) {
            try {
                auto lib = std::make_shared<DynamicLibrary>(path);
                auto getName = lib->getSymbol<const char* (*)()>("getName");
                std::string name = getName();
                if (_libraries.find(name) != _libraries.end()) {
                    throw Shared::CustomError("Plugin " + name + " already loaded");
                }
                auto getType = lib->getSymbol<RayTracer::Plugins::PluginType (*)()>("getType");
                auto type = getType();

                CreateEntityFunc createEntityFunc = nullptr;
                CreateDecoratorFunc createDecoratorFunc = nullptr;
                CreateSkyboxFunc createSkyboxFunc = nullptr;
                CreateGraphModuleFunc createGraphModuleFunc = nullptr;

                switch (type) {
                    case Plugins::PluginType::Entity:
                        createEntityFunc = (lib->getSymbol<CreateEntityFunc>("create"));
                        entityFactory.registerPlugin(name, createEntityFunc);
                        _factories[name] = &entityFactory;
                        _libraries[name] = type;
                        break;
                    case Plugins::PluginType::Decorator:
                        createDecoratorFunc = (lib->getSymbol<CreateDecoratorFunc>("create"));
                        decoratorFactory.registerPlugin(name, createDecoratorFunc);
                        _factories[name] = &decoratorFactory;
                        _libraries[name] = type;
                        break;
                    case Plugins::PluginType::Skybox:
                        createSkyboxFunc = (lib->getSymbol<CreateSkyboxFunc>("create"));
                        skyboxFactory.registerPlugin(name, createSkyboxFunc);
                        _factories[name] = &skyboxFactory;
                        _libraries[name] = type;
                        break;
                    case Plugins::PluginType::Graphical:
                        createGraphModuleFunc = (lib->getSymbol<CreateGraphModuleFunc>("create"));
                        graphModuleFactory.registerPlugin(name, createGraphModuleFunc);
                        _factories[name] = &graphModuleFactory;
                        _libraries[name] = type;
                        break;
                    default:
                        throw Shared::CustomError("Unknown plugin type");
                }
                return lib;
            } catch (const Shared::CustomError &e) {
                std::cerr << e.what() << std::endl;
            }
            return nullptr;
        }

        void PluginLoader::loadLibraries(const std::string &directory) {
            for (const auto &entry : fs::directory_iterator(directory)) {
                if (entry.path().extension() == ".so" || entry.path().extension() == ".dylib") {
                    try {
                        _loadedLibraries.push_back(loadPlugin(entry.path()));
                    } catch (const Shared::CustomError &e) {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        }

        std::unordered_map<std::string, RayTracer::Plugins::PluginType> PluginLoader::getLibraries() const {
            return _libraries;
        }

        std::unordered_map<std::string, FactoryVariant> PluginLoader::getFactories() const {
            return _factories;
        }
    }
}