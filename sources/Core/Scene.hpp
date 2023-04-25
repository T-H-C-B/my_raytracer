//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_SCENE_HPP
#define MY_RAYTRACER_SCENE_HPP

#include "IEntity.hpp"
#include <string>
#include <unordered_map>
#include "IEntity.hpp"

namespace RayTracer {
    namespace Core {

        class Scene {
            public:
                Scene(const std::string &directory);
                void init();
                void close();
                std::vector<IEntity &> getEntities(EntityType type);
                std::unordered_map<EntityType type, std::vector<IEntity *>> getEntities();
                ~Scene();
            private:
                std::string _directory;
                std::unordered_map<EntityType type, std::vector<IEntity *>> _entities;
                IEntity *actualCamera;
        };

    } // RayTracer
} // Core

#endif //MY_RAYTRACER_SCENE_HPP
