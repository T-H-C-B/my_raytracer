//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "IEntity.hpp"
#include "LibType.hpp"

namespace RayTracer::Core {

        class Scene {
            public:
                explicit Scene(const std::string &path);
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
}