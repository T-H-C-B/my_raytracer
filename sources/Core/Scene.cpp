#include "SettingWrapper.hpp"
#include "ConfigWrapper.hpp"
//
// Created by Clément Lagasse on 24/04/2023.
//

#include <cstring>
#include "Scene.hpp"
#include "libconfig.h++"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "ConfigWrapper.hpp"
#include <cstring>

namespace RayTracer {
    namespace Core {
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
            } catch (const libconfig::FileIOException &fioex) {
                throw RayTracer::Shared::ConfigError("Scene", "I/O error while reading file: " + _path);
            } catch (const libconfig::ParseException &pex) {
                throw RayTracer::Shared::ConfigError("Scene", "Parse error at " + std::string(pex.getFile()) + ":" + std::to_string(pex.getLine())
                                           + " - " + pex.getError());
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
                        if (loadOtherScenes.isGroup()) {
                            const RayTracer::Shared::SettingWrapper &paths = loadOtherScenes["paths"];
                            if (paths.isArray() || paths.isList() || paths.isGroup()) {
                                for (int j = 0; j < paths.getLength(); j++) {
                                    _path = static_cast<std::string>(paths[j]);
                                    init(factories, _libraries);
                                }
                            }
                        }
                    } else {
                        _path = configItems.lookup<std::string>("paths");
                        init(factories, _libraries);
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
            _entities.clear();
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
                setNextCamera();
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
            if (cameras.empty()) {

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
