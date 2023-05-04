//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Scene.hpp"
#include "libconfig.h++"
#include "PluginType.hpp"

namespace RayTracer {
    namespace Core {
        Scene::Scene(const std::string &path) {
            _path = path;
            _actualCamera = nullptr;
            _currentSkyBox = 0;
        }

        void Scene::init(const std::unordered_map<std::string, RayTracer::Core::FactoryVariant>& factories,
                         const std::unordered_map<std::string, RayTracer::Plugins::PluginType>& _libraries) {
            libconfig::Config cfg;
            try {
                cfg.readFile(_path.c_str());
            } catch (const libconfig::FileIOException &fioex) {
                std::cerr << "I/O error while reading file: " << _path << std::endl;
                return;
            } catch (const libconfig::ParseException &pex) {
                std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                          << " - " << pex.getError() << std::endl;
                return;
            }
            libconfig::Setting &root = cfg.getRoot();

            for (const auto &factory : factories) {
                const std::string &factoryName = factory.first;
                if (factoryName == "decorator") {
                    if (root.exists(factoryName)) {
                        libconfig::Setting &configItems = root[factoryName];
                        if (configItems.isList() || configItems.isArray()) {
                            for (int i = 0; i < configItems.getLength(); ++i) {
                                libconfig::Setting &configItem = configItems[i];
                                createObjectFromFactory(factory.second, configItem);
                            }
                        } else {
                            createObjectFromFactory(factory.second, configItems);
                        }
                    }
                }
            }

            for (const auto &factory : factories) {
                const std::string &factoryName = factory.first;
                if (root.exists(factoryName)) {
                    libconfig::Setting &configItems = root[factoryName];
                    if (configItems.isList() || configItems.isArray()) {
                        for (int i = 0; i < configItems.getLength(); ++i) {
                            libconfig::Setting &configItem = configItems[i];
                            createObjectFromFactory(factory.second, configItem);
                        }
                    } else {
                        createObjectFromFactory(factory.second, configItems);
                    }
                }
            }
        }

        void Scene::createObjectFromFactory(const RayTracer::Core::FactoryVariant &factoryVariant,
                                            libconfig::Setting &configItem) {
            FactoryVisitor visitor{configItem, this, _decorators, _skyBox, _entities, _graphs};
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
                //add throw
            }
            if (_actualCamera == nullptr) {
                _actualCamera = cameras[0];
            } else {
                auto it = std::find(cameras.begin(), cameras.end(), _actualCamera);
                if (it == cameras.end()) {
                    //throw error
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