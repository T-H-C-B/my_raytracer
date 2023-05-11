#include "SettingWrapper.hpp"
//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "IEntity.hpp"
#include "ISkyBox.hpp"
#include <iostream>
#include "CustomError.hpp"
#include <string>
#include <variant>
#include <filesystem>
#include <memory>
#include "FactoryTemplate.hpp"
#include "IDecorator.hpp"
#include "IGraphModule.hpp"
#include "PluginType.hpp"
#include "IPrimitive.hpp"
#include "Material.hpp"

namespace RayTracer {
    namespace Core {

        using FactoryVariant = std::variant<Factory<RayTracer::Core::IEntity> *,
        Factory<RayTracer::Plugins::Decorators::IDecorator> *,
        Factory<RayTracer::Plugins::Skyboxes::ISkyBox> *,
        Factory<RayTracer::Plugins::Graphics::IGraphModule> *>;

        class Scene {
            public:
                explicit Scene(const std::string &path);
                void init(const std::unordered_map<std::string, RayTracer::Core::FactoryVariant>& factories,
                          const std::unordered_map<std::string, RayTracer::Plugins::PluginType>& _libraries);
                void close();
                std::vector<IEntity *> getEntities(EntityType type);
                std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> getEntities();
                IEntity *getActualCamera();
                void setNextCamera();
                void setPreviousCamera();
                RayTracer::Plugins::Skyboxes::ISkyBox *getActualSkyBox();
                void setNextSkyBox();
                void setPreviousSkyBox();
                void createObjectFromFactory(const RayTracer::Core::FactoryVariant &factoryVariant,
                                             const RayTracer::Shared::SettingWrapper &configItem, std::string name);
                void searchDecorators(const RayTracer::Shared::SettingWrapper &setting,
                                      const std::unordered_map<std::string, RayTracer::Core::FactoryVariant>& factories);
                ~Scene() = default;
            private:
                std::vector<std::string> _alreadyRead;
                std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> _entities;
                std::vector<RayTracer::Plugins::Graphics::IGraphModule *> _graphs;
                std::unordered_map<std::string, RayTracer::Plugins::Decorators::IDecorator *> _decorators;
                int _currentSkyBox;
                std::string _path;
                IEntity *_actualCamera;
                std::vector<RayTracer::Plugins::Skyboxes::ISkyBox *> _skyBox;
        };
        template <template <typename> class FactoryTemplate, typename ProductType>
        ProductType* getProductType(FactoryTemplate<ProductType>*);

        template <typename FactoryPtr>
        using ProductTypeOfFactory = decltype(getProductType(std::declval<FactoryPtr>()));

    }
}
