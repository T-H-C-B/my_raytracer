//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include <memory>
#include <vector>
#include "Scene.hpp"

namespace RayTracer::Core {

    class Scene;
    class SceneManager {
    public:
        SceneManager() = default;

        ~SceneManager() = default;

        std::unique_ptr<RayTracer::Core::Scene> &getCurrentScene();

        void setNextScene();

        void setPreviousScene();

    private:
        unsigned int _currentScene;
        std::vector<std::unique_ptr<RayTracer::Core::Scene>> _scenes;

    };
}