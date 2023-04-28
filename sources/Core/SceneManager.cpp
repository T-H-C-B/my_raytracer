//
// Created by Clément Lagasse on 24/04/2023.
//

#include "SceneManager.hpp"

namespace RayTracer {
    namespace Core {
            SceneManager::SceneManager() {

            }
            std::unique_ptr<RayTracer::Core::Scene> &SceneManager::getCurrentScene() {
                return _scenes[_currentScene];
            }

            void SceneManager::setNextScene() {
                if (_currentScene + 1 < _scenes.size())
                    _currentScene++;
            }

            void SceneManager::setPreviousScene() {
                if (_currentScene > 0)
                    _currentScene--;
            }
    } // RayTracer
} // Core