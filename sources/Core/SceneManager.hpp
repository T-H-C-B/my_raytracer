//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ISCENEMANAGER_HPP
#define MY_RAYTRACER_ISCENEMANAGER_HPP

#include "IScene.hpp"
#include <memory>

namespace RayTracer {
    namespace Core {

        class ISceneManager {
        public:
            ISceneManager() = default;
            ~ISceneManager() = default;

            std::unique_ptr<IScene> &getCurrentScene();
            void setNextScene();
            void setPreviousScene();
        private:
            unsigned int _currentScene;
            std::vector<std::unique_ptr<IScene>> _scenes;

        };

    } // RayTracer
} // Core

#endif //MY_RAYTRACER_ISCENEMANAGER_HPP
