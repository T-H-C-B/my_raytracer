//
// Created by Clément Lagasse on 24/04/2023.
//

#include <filesystem>
#include <algorithm>
#include <iostream>
#include "SceneManager.hpp"
#include "CustomError.hpp"

namespace fs = std::filesystem;

namespace RayTracer {
    namespace Core {
        SceneManager::SceneManager(const std::string &directory) {
            _currentScene = 0;
            std::vector<std::string> filepaths;

            for (const auto &entry : fs::directory_iterator(directory)) {
                try {
                    if (entry.is_regular_file() && entry.path().extension() == ".cfg") {
                        std::string filePath = entry.path().string();
                        filepaths.push_back(filePath);
                    }
                } catch (const fs::filesystem_error &e) {
                    std::cerr << "Error processing scene at " << entry.path() << ": " << e.what() << std::endl;
                }
            }
            std::sort(filepaths.begin(), filepaths.end());

            for (const auto &filePath : filepaths) {
                std::cout << "Loading scene: " << filePath << std::endl;
                _scenes.push_back(std::make_unique<RayTracer::Core::Scene>(filePath));
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