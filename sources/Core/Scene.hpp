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
#include <libconfig.h++>
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
                                             libconfig::Setting &configItem, std::string name);
                void searchDecorators(libconfig::Setting &setting,
                                      const std::unordered_map<std::string, RayTracer::Core::FactoryVariant>& factories);
                ~Scene() = default;
            private:
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

        struct FactoryVisitor {
            libconfig::Setting &configItem;
            Scene *scene;
            std::vector<RayTracer::Plugins::Graphics::IGraphModule *> &graphModules;
            std::vector<RayTracer::Plugins::Skyboxes::ISkyBox *> &skyBoxes;
            std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> &_entitiesFac;
            std::unordered_map<std::string, RayTracer::Plugins::Decorators::IDecorator *> &_decorators;
            std::string _name;

            FactoryVisitor(libconfig::Setting &configItem, Scene *scene,
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
                                libconfig::Setting &decoratorsList = configItem["Decorator"];
                                for (int i = 0; i < decoratorsList.getLength(); ++i) {
                                    std::string decorator_name = decoratorsList[i].getName();
                                    if (decoratorsList[i].exists("Color")) {
                                        if (decoratorsList[i].exists("Color")) {
                                            libconfig::Setting &colorSetting = decoratorsList[i]["Color"];
                                            decorator_name += "_" + std::to_string(static_cast<int>(colorSetting.lookup("r")));
                                            decorator_name += "_" + std::to_string(static_cast<int>(colorSetting.lookup("g")));
                                            decorator_name += "_" + std::to_string(static_cast<int>(colorSetting.lookup("b")));
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
                    libconfig::Setting &colorSetting = configItem["Color"];
                    _namedecorator += "_" + std::to_string(static_cast<int>(colorSetting.lookup("r")));
                    _namedecorator += "_" + std::to_string(static_cast<int>(colorSetting.lookup("g")));
                    _namedecorator += "_" + std::to_string(static_cast<int>(colorSetting.lookup("b")));
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
    }
}
