//
// Created by Clément Lagasse on 24/04/2023.
//

#include <cstring>
#include "Scene.hpp"
#include "libconfig.h++"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include <cstring>
#include "ConfigWrapper.hpp"
#include "ConfigError.hpp"

namespace RayTracer {
    namespace Core {

        struct FactoryVisitor {
            const RayTracer::Shared::SettingWrapper &configItem;
            Scene *scene;
            std::vector<RayTracer::Plugins::Graphics::IGraphModule *> &graphModules;
            std::vector<RayTracer::Plugins::Skyboxes::ISkyBox *> &skyBoxes;
            std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> &_entitiesFac;
            std::unordered_map<std::string, RayTracer::Plugins::Decorators::IDecorator *> &_decorators;
            std::string _name;

            FactoryVisitor(const RayTracer::Shared::SettingWrapper &configItem, Scene *scene,
                           std::unordered_map<std::string, RayTracer::Plugins::Decorators::IDecorator *> &_decorators,
                           std::vector<RayTracer::Plugins::Skyboxes::ISkyBox *> &skyBoxes,
                           std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> &_entities,
                           std::vector<RayTracer::Plugins::Graphics::IGraphModule *> &graphModules,
                           std::string name)
                    : configItem(configItem), scene(scene), _decorators(_decorators),
                      skyBoxes(skyBoxes), _entitiesFac(_entities), graphModules(graphModules), _name(std::move(name)) {}

            void operator()(Factory<RayTracer::Core::IEntity> *factory) {
                createEntity(factory);
            }

            void operator()(Factory<RayTracer::Plugins::Decorators::IDecorator> *factory) {
                createDecorator(factory);
            }

            void operator()(Factory<RayTracer::Plugins::Skyboxes::ISkyBox> *factory) {
                createSkybox(factory);
            }

            void operator()(Factory<RayTracer::Plugins::Graphics::IGraphModule> *factory) {
                createGraphModule(factory);
            }

            void createEntity(Factory<RayTracer::Core::IEntity> *factory) {
                IEntity *product = factory->create(_name, configItem);
                if (product != nullptr) {
                    if (product->getType() == EntityType::Primitive) {
                        auto *primitive = dynamic_cast<RayTracer::Plugins::Primitives::IPrimitive *>(product);
                        if (primitive != nullptr) {
                            if (configItem.exists("Decorator")) {
                                const RayTracer::Shared::SettingWrapper &decoratorsList = configItem["Decorator"];
                                for (int i = 0; i < decoratorsList.getLength(); ++i) {
                                    std::string decorator_name = decoratorsList[i].getName();
                                    if (decoratorsList[i].exists("Color")) {
                                        const RayTracer::Shared::SettingWrapper &colorSetting = decoratorsList[i]["Color"];
                                        decorator_name += "_" + std::to_string(static_cast<int>(colorSetting.lookup<int>("r")));
                                        decorator_name += "_" + std::to_string(static_cast<int>(colorSetting.lookup<int>("g")));
                                        decorator_name += "_" + std::to_string(static_cast<int>(colorSetting.lookup<int>("b")));
                                    } else if (decoratorsList[i].exists("path")) {
                                        decorator_name += "_" + decoratorsList[i].lookup<std::string>("path");
                                    }
                                    if (_decorators.find(decorator_name) != _decorators.end()) {
                                        RayTracer::Shared::Material *material = primitive->getMaterial();
                                        material->addDecorator(_decorators[decorator_name]);
                                    } else {
                                        std::cerr << "Decorator \"" << decorator_name << "\" not found" << std::endl;
                                    }
                                }
                            }
                        }
                        _entitiesFac[product->getType()].push_back(product);
                    } else {
                        _entitiesFac[product->getType()].push_back(product);
                    }
                }
            }


            void createGraphModule(Factory<RayTracer::Plugins::Graphics::IGraphModule> *factory) {
                RayTracer::Plugins::Graphics::IGraphModule *product = factory->create(_name, configItem);
                if (product != nullptr) {
                    graphModules.push_back(product);
                }
            }

            void createDecorator(Factory<RayTracer::Plugins::Decorators::IDecorator> *factory) {
                std::string _namedecorator = _name;
                if (configItem.exists("Color")) {
                    const RayTracer::Shared::SettingWrapper &colorSetting = configItem["Color"];
                    _namedecorator += "_" + std::to_string(static_cast<int>(colorSetting.lookup<int>("r")));
                    _namedecorator += "_" + std::to_string(static_cast<int>(colorSetting.lookup<int>("g")));
                    _namedecorator += "_" + std::to_string(static_cast<int>(colorSetting.lookup<int>("b")));
                } else if (configItem.exists("path")) {
                    _namedecorator += "_" + configItem.lookup<std::string>("path");
                }
                RayTracer::Plugins::Decorators::IDecorator *decorator = factory->create(_name, configItem);
                if (decorator != nullptr) {
                    _decorators.emplace(_namedecorator, decorator);
                }
            }


            void createSkybox(Factory<RayTracer::Plugins::Skyboxes::ISkyBox> *factory) {
                RayTracer::Plugins::Skyboxes::ISkyBox *product = factory->create(_name, configItem);
                if (product != nullptr) {
                    skyBoxes.push_back(product);
                }
            }
        };

        Scene::Scene(const std::string &path) {
            _path = path;
            _actualCamera = nullptr;
            _currentSkyBox = 0;
        }

        void Scene::init(const std::unordered_map<std::string, RayTracer::Core::FactoryVariant>& factories,
                         const std::unordered_map<std::string, RayTracer::Plugins::PluginType>& _libraries) {
            for (auto &_alreadyRead : _alreadyRead) {
                if (_alreadyRead == _path)
                    throw RayTracer::Shared::ConfigError("Scene", "Circular dependency detected: " + _path);
            }
            _alreadyRead.push_back(_path);
            RayTracer::Shared::ConfigWrapper cfg;
            try {
                cfg.readFile(_path.c_str());
            } catch (const RayTracer::Shared::FileIOException &ex) {
                throw RayTracer::Shared::ConfigError("Scene", "I/O error while reading file: " + _path);
            } catch (const RayTracer::Shared::ParseException &pex) {
                throw RayTracer::Shared::ConfigError("Scene", "Parse error");
            }
            const RayTracer::Shared::SettingWrapper &root = cfg.getRoot();

            searchDecorators(root, factories);
            for (int i = 0; i < root.getLength(); ++i) {
                const RayTracer::Shared::SettingWrapper &configItems = root[i];
                const std::string configName = configItems.getName();

                auto factoryIt = factories.find(configName);
                if (factoryIt != factories.end()) {
                    if (strcmp(configItems.getName(), "LoadOtherScenes") == 0) {
                        const RayTracer::Shared::SettingWrapper &loadOtherScenes = configItems["paths"];
                            const RayTracer::Shared::SettingWrapper &paths = loadOtherScenes["paths"];
                            if (paths.isArray() || paths.isList() || paths.isGroup()) {
                                for (int j = 0; j < paths.getLength(); j++) {
                                    _path = paths[j].getValueAsString();
                                    init(factories, _libraries);
                                }
                            } else {
                                _path = configItems.lookup<std::string>("paths");
                                init(factories, _libraries);
                            }
                    }
                    if (configItems.isList() || configItems.isArray()) {
                        for (int j = 0; j < configItems.getLength(); ++j) {
                            const RayTracer::Shared::SettingWrapper &configItem = configItems[j];
                            createObjectFromFactory(factoryIt->second, configItem, configName);
                        }
                    } else {
                        createObjectFromFactory(factoryIt->second, configItems, configName);
                    }
                }
            }
            try {
                getActualCamera();
            } catch (const RayTracer::Shared::CustomError &ex) {
                throw RayTracer::Shared::ConfigError("Scene", "No camera found");
            }
            _alreadyRead.clear();
        }

        void Scene::searchDecorators(const RayTracer::Shared::SettingWrapper &setting, const std::unordered_map<std::string, RayTracer::Core::FactoryVariant>& factories) {
            if (setting.isGroup() || setting.isArray() || setting.isList()) {
                for (int i = 0; i < setting.getLength(); ++i) {
                    searchDecorators(setting[i], factories);
                }
            }
            if (!setting.getName())
                return;
            if (strcmp(setting.getName(), "Decorator") == 0) {
                for (const auto &factory : factories) {
                    const std::string &factoryName = factory.first;
                    if (setting.isList() || setting.isArray() || setting.isGroup()) {
                        for (int i = 0; i < setting.getLength(); ++i) {
                            const RayTracer::Shared::SettingWrapper &configItem = setting[i];
                            if (factoryName == configItem.getName()) {
                                createObjectFromFactory(factory.second, configItem, factoryName);
                            }
                        }
                    } else {
                        if (factoryName == setting[0].getName()) {
                            createObjectFromFactory(factory.second, setting[0], factoryName);
                        }
                    }
                }
            }
        }


        void Scene::createObjectFromFactory(const RayTracer::Core::FactoryVariant &factoryVariant,
                                            const RayTracer::Shared::SettingWrapper &configItem, std::string name) {
            FactoryVisitor visitor{configItem, this, _decorators, _skyBox, _entities, _graphs, name};
            std::visit(visitor, factoryVariant);
        }

        void Scene::close() {
            for (auto &entityGroup : _entities) {
                for (IEntity *entity : entityGroup.second) {
                    delete entity;
                }
                entityGroup.second.clear();
            }
            getEntities(EntityType::Camera).clear();
            _entities.clear();
            _actualCamera = nullptr;
        }



        std::vector<IEntity *> Scene::getEntities(EntityType type) {
            std::vector<IEntity *> entities;

            for (auto &entityGroup : _entities) {
                if (entityGroup.first == type) {
                    for (IEntity *entity : entityGroup.second) {
                        entities.push_back(entity);
                    }
                }
            }
            return entities;
        }

        std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> Scene::getEntities() {
            return _entities;
        }


        IEntity *Scene::getActualCamera() {
            if (_actualCamera == nullptr) {
                try {
                    setNextCamera();
                } catch (const RayTracer::Shared::ConfigError &ex) {
                    throw RayTracer::Shared::CustomError("Scene No camera found in scene: " + _path);
                }
            }
            return _actualCamera;
        }

        RayTracer::Plugins::Skyboxes::ISkyBox *Scene::getActualSkyBox() {
            if (!_skyBox.empty()) {
                return _skyBox[_currentSkyBox];
            }
            return nullptr;
        }

        void Scene::setNextSkyBox() {
            if (!_skyBox.empty()) {
                _currentSkyBox = (_currentSkyBox + 1) % _skyBox.size();
            }
        }

        void Scene::setPreviousSkyBox() {
            if (!_skyBox.empty()) {
                _currentSkyBox = (_currentSkyBox - 1 + _skyBox.size()) % _skyBox.size();
            }
        }


        void Scene::setNextCamera() {

            std::vector<IEntity *> cameras = getEntities(EntityType::Camera);
            try {
                if (cameras.empty()) {
                    std::cout << _path << std::endl;
                    throw RayTracer::Shared::ConfigError("Scene", "No camera found");
                }
                if (_actualCamera == nullptr) {
                    _actualCamera = cameras[0];
                } else {
                    auto it = std::find(cameras.begin(), cameras.end(), _actualCamera);
                    if (it == cameras.end()) {

                    }
                    ++it;
                    if (it == cameras.end()) {
                        _actualCamera = cameras[0];
                    } else {
                        _actualCamera = *it;
                    }
                }
            } catch (const RayTracer::Shared::ConfigError& e) {
                std::cerr << "Error in Scene::setNextCamera(): " << e.what() << std::endl;
                throw e;
            }
        }

        void Scene::setPreviousCamera() {
            std::vector<IEntity *> cameras = getEntities(EntityType::Camera);
            if (cameras.empty()) {
                //throw error
            }
            if (_actualCamera == nullptr) {
                _actualCamera = cameras[0];
            } else {
                auto it = std::find(cameras.begin(), cameras.end(), _actualCamera);
                if (it == cameras.end()) {
                    //throw error
                }
                if (it == cameras.begin()) {
                    _actualCamera = cameras[cameras.size() - 1];
                } else {
                    --it;
                    _actualCamera = *it;
                }
            }
        }

    } // RayTracer
} // Core
