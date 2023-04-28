//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <memory>
#include <vector>
#include "Scene.hpp"
#include <unordered_map>

namespace RayTracer {
    namespace Core {

        class SceneManager {
        public:
            SceneManager();
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
