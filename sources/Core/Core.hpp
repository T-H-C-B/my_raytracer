//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <memory>
#include "FactoryTemplate.hpp"
#include "Image.hpp"
#include "SceneManager.hpp"
#include "IGraphModule.hpp"
#include "IDecorator.hpp"
#include "ISkyBox.hpp"
#include "EventManager.hpp"
#include "PluginLoader.hpp"

namespace RayTracer {
    namespace Core {

        class Core {
        public:
            explicit Core(const std::string &graphModuleName, const std::string &configDir = "./scenes/", const std::string &pluginDir = "./plugins/");
            ~Core() = default;

            int run();
            void setGraphModule(RayTracer::Plugins::Graphics::IGraphModule* graphModule);
            void setAmbientLight(float ambientLight);
            void setOpacity(float opacity);
            float getAmbientLight() const;
            float renderingPercentage() const;

        private:
            void handleEvents();
            void quitCore();
            void goForward();
            void goBackward();
            void goLeft();
            void goRight();
            void goUp();
            void goDown();
            void lookLeft();
            void lookRight();
            void lookUp();
            void lookDown();
            void goNextScene();
            void goPreviousScene();
            void goNextCamera();
            void goPreviousCamera();
            void manageRenderingPercentage();

            Factory<RayTracer::Plugins::Graphics::IGraphModule> _graphModuleFactory;
            Factory<RayTracer::Core::IEntity> _entityFactory;
            Factory<RayTracer::Plugins::Decorators::IDecorator> _decoratorFactory;
            Factory<RayTracer::Plugins::Skyboxes::ISkyBox> _skyBoxFactory;

            RayTracer::Plugins::Graphics::IGraphModule *_graphModule;
            EventManager _eventManager;
            SceneManager _sceneManager;
            PluginLoader _pluginLoader;

            Image image;
            bool _isRunning;
            bool _imageUpdated;
            std::string _configDir;
            std::string _pluginDir;
            bool _catchErrors;
            float _ambientLight;
            float _renderingPercentage;
        };

    } // RayTracer
} // Core
