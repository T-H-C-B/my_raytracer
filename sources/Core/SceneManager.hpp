//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once
#include <memory>
#include "Scene.hpp"

namespace RayTracer {
    namespace Core {

        class SceneManager {
        public:
            SceneManager(const std::string &Directory);
            ~SceneManager() = default;

            std::unique_ptr<RayTracer::Core::Scene> &getCurrentScene();
            void setNextScene();
            void setPreviousScene();
        private:
            unsigned int _currentScene;
            std::vector<std::unique_ptr<RayTracer::Core::Scene>> _scenes;

        };

    } // RayTracer
} // Core
