//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <libconfig.h++>
#include "IEntity.hpp"
#include "DynamicLibrary.hpp"

namespace fs = std::filesystem;


namespace RayTracer {
    namespace Core {
        class SceneLoader {
        public:
            SceneLoader(const std::string &configPath, const std::string &libDir);

            void loadScene();

            void loadLibraries();

            void run();

        private:
            std::string configPath;
            std::string libDir;
            libconfig::Config config;
            std::vector <std::tuple<std::string, std::shared_ptr < DynamicLibrary>>>
            libraries;
            std::vector<IEntity *> entities;
        };
    }
}
#endif // SCENELOADER_HPP
