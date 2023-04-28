//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_SCENE_HPP
#define MY_RAYTRACER_SCENE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "IEntity.hpp"

namespace RayTracer {
    namespace Core {

        class Scene {
            public:
                Scene(const std::string &path);
                void init();
                void close();
                std::vector<IEntity *> getEntities(EntityType type);
                std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> getEntities();
                IEntity *getActualCamera();
                void setNextCamera();
                void setPreviousCamera();
                ~Scene() = default;
            private:
                std::string _path;
                std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> _entities;
                IEntity *actualCamera;
        };

    } // RayTracer
} // Core

#endif //MY_RAYTRACER_SCENE_HPP
