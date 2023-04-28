//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "IEntity.hpp"
#include "LibType.hpp"
#include "IEntity.hpp"
#include "IDecorator.hpp"
#include "ISkyBox.hpp"
#include "IGraphModule.hpp"
#include "FactoryTemplate.hpp"
#include "libconfig.h++"
#include <iostream>

namespace RayTracer::Core {

        using FactoryVariant = std::variant<Factory<RayTracer::Core::IEntity> *,
                Factory<RayTracer::Plugins::Decorators::IDecorator> *,
                Factory<RayTracer::Plugins::Skyboxes::ISkyBox> *,
                Factory<RayTracer::Plugins::Graphics::IGraphModule> *>;

        struct EntityCreator {
            const libconfig::Setting& setting;

            RayTracer::Core::IEntity* operator()(Factory<RayTracer::Core::IEntity>* factory) const {
                return factory->create("TMP", setting);
            }

            RayTracer::Plugins::Decorators::IDecorator* operator()(Factory<RayTracer::Plugins::Decorators::IDecorator>* factory) const {
                return factory->create("TMP", setting);
            }

            RayTracer::Plugins::Skyboxes::ISkyBox* operator()(Factory<RayTracer::Plugins::Skyboxes::ISkyBox>* factory) const {
                return factory->create("TMP", setting);
            }

            RayTracer::Plugins::Graphics::IGraphModule* operator()(Factory<RayTracer::Plugins::Graphics::IGraphModule>* factory) const {
                return factory->create("TMP", setting);
            }
        };

        class Scene {
            public:
                explicit Scene(const std::string &path);
                void init(const std::unordered_map<std::string, FactoryVariant>& factories,
                      const std::unordered_map<std::string, LibType>& libTypes);

                void close();
                // ON A FAIS DE LA MERDE ??? TODO

                //std::vector<IEntity *> getEntities(EntityType type);
                //std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> getEntities();
                IEntity *getActualCamera();
                void setNextCamera();
                void setPreviousCamera();
                ~Scene() = default;
            private:
                std::string _path;

                std::unordered_map<LibType, std::vector<RayTracer::Core::IEntity*>> _entityEntities;
                std::unordered_map<LibType, std::vector<RayTracer::Plugins::Decorators::IDecorator*>> _decoratorEntities;
                std::unordered_map<LibType, std::vector<RayTracer::Plugins::Skyboxes::ISkyBox*>> _skyboxEntities;
                std::unordered_map<LibType, std::vector<RayTracer::Plugins::Graphics::IGraphModule*>> _graphModuleEntities;

                IEntity *actualCamera;
        };
}