//
// Created by Clément Lagasse on 24/04/2023.
//

#include <filesystem>
#include <iostream>
#include "SceneManager.hpp"
#include "CustomError.hpp"

namespace fs = std::filesystem;

namespace RayTracer {
    namespace Core {
        SceneManager::SceneManager(std::string &directory) {
            _currentScene = 0;
            try {
                for (const auto &entry : fs::directory_iterator(directory)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".cfg") {
                        std::string filePath = entry.path().string();
                        _scenes.push_back(std::make_unique<RayTracer::Core::Scene>(filePath));
                    }
                }
            } catch (const fs::filesystem_error &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        std::unique_ptr<RayTracer::Core::Scene> &SceneManager::getCurrentScene() {
            if (_scenes.empty()) {
                throw RayTracer::Shared::CustomError("No scenes available.");
            }
            return _scenes[_currentScene];
        }

        void SceneManager::setNextScene() {
            if (_scenes.empty()) {
                throw RayTracer::Shared::CustomError("No scenes available.");
            }
            _currentScene = (_currentScene + 1) % _scenes.size();
        }

        void SceneManager::setPreviousScene() {
            if (_scenes.empty()) {
                throw RayTracer::Shared::CustomError("No scenes available.");
            }
            _currentScene = (_currentScene - 1 + _scenes.size()) % _scenes.size();
        }


    } // RayTracer
} // Core