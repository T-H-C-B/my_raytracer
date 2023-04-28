//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Scene.hpp"
#include "libconfig.h++"
#include <iostream>
#include "CustomError.hpp"

namespace RayTracer {
    namespace Core {
        Scene::Scene(const std::string &path) {
            _path = path;
            actualCamera = nullptr;
        }

        void Scene::init(std::unordered_map<std::string, FactoryVariant> factories, std::unordered_map<std::string, LibType> libTypes) {
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

            for (const auto& libTypePair : libTypes) {
                const std::string& libName = libTypePair.first;
                const LibType& libType = libTypePair.second;
                libconfig::Setting& settings = cfg.lookup(libName);

                std::string factoryName = libName;
                if (factoryName.back() == 's') {
                    factoryName.pop_back();
                }

                auto factoryIt = factories.find(factoryName);
                if (factoryIt == factories.end()) {
                    std::cerr << "Factory not found for library " << libName << std::endl;
                    continue;
                }

                for (int i = 0; i < settings.getLength(); ++i) {
                    try {
                        IEntity* entity = factoryIt->second(settings[i]);
                        // addDecorator
                        entities.push_back(entity);
                    } catch (const std::exception &e) {
                        std::cerr << "Error creating entity from library " << libName << ": " << e.what()
                                  << std::endl;
                        continue;
                    }
                }
            }
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
            std::vector<IEntity *> result;

            auto it = _entities.find(type);
            if (it != _entities.end()) {
                result.insert(result.end(), it->second.begin(), it->second.end());
            }

            return result;
        }

        std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> Scene::getEntities() {
            return _entities;
        }

        IEntity *Scene::getActualCamera() {
            return actualCamera;
        }

        void Scene::setNextCamera() {
            std::vector<IEntity *> cameras = getEntities(EntityType::CAMERA);
            if (cameras.empty()) {
                throw CustomError("No camera found");
            }
            if (actualCamera == nullptr) {
                actualCamera = cameras[0];
            } else {
                auto it = std::find(cameras.begin(), cameras.end(), actualCamera);
                if (it == cameras.end()) {
                    throw CustomError("Camera not found");
                }
                ++it;
                if (it == cameras.end()) {
                    actualCamera = cameras[0];
                } else {
                    actualCamera = *it;
                }
            }
        }

        void Scene::setPreviousCamera() {
            std::vector<IEntity *> cameras = getEntities(EntityType::CAMERA);
            if (cameras.empty()) {
                throw CustomError("No camera found");
            }
            if (actualCamera == nullptr) {
                actualCamera = cameras[0];
            } else {
                auto it = std::find(cameras.begin(), cameras.end(), actualCamera);
                if (it == cameras.end()) {
                    throw CustomError("Camera not found");
                }
                if (it == cameras.begin()) {
                    actualCamera = cameras[cameras.size() - 1];
                } else {
                    --it;
                    actualCamera = *it;
                }
            }
        }


    } // RayTracer
} // Core