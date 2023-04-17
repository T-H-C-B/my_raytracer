//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <string>
#include <vector>
#include <memory>
#include <libconfig.h++>
#include "IEntity.hpp"
#include "DynamicLibrary.hpp"

#if defined(__APPLE__) || defined(__MACH__)
    #define OS_MAC
#elif defined(__linux__)
    #define OS_LINUX
#endif

#ifdef OS_MAC
    namespace fs = std::__fs::filesystem;
#elif defined(OS_LINUX)
    namespace fs = std::filesystem;
#endif

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
    std::vector<std::tuple<std::string, std::shared_ptr<DynamicLibrary>>> libraries;
    std::vector<IEntity *> entities;
};

#endif // SCENELOADER_HPP
