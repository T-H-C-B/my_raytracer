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

        void Scene::init() {
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
                //add throw
            }
            if (actualCamera == nullptr) {
                actualCamera = cameras[0];
            } else {
                auto it = std::find(cameras.begin(), cameras.end(), actualCamera);
                if (it == cameras.end()) {
                    //throw error
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
                //throw error
            }
            if (actualCamera == nullptr) {
                actualCamera = cameras[0];
            } else {
                auto it = std::find(cameras.begin(), cameras.end(), actualCamera);
                if (it == cameras.end()) {
                    //throw error
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