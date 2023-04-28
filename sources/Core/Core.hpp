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

namespace RayTracer {
    namespace Core {

        class Core {
        public:
            Core(const std::string &graphModuleName, const std::string &configDir = "./scenes/", const std::string &pluginDir = "./plugins/");
            ~Core() = default;

            int run();
            void setGraphModule(std::unique_ptr<RayTracer::Plugins::Graphics::IGraphModule> graphModule);

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

        private:
            void handleEvents();


            Factory<RayTracer::Plugins::Graphics::IGraphModule> _graphModuleFactory;
            Factory<RayTracer::Core::IEntity> _entityFactory;
            Factory<RayTracer::Plugins::Decorators::IDecorator> _decoratorFactory;
            Factory<RayTracer::Plugins::Skyboxes::ISkyBox> _skyBoxFactory;

            std::unique_ptr<Plugins::Graphics::IGraphModule> _graphModule;
            EventManager _eventManager;

            Image image;
            bool _isRunning;
            bool _imageUpdated;
            std::string _configDir;
            std::string _pluginDir;
            bool _catchErrors;
        };

    } // RayTracer
} // Core
