//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include "SceneLoader.hpp"
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <libconfig.h++>
#include "ICamera.hpp"
#include "Image.hpp"
#include <limits>

SceneLoader::SceneLoader(const std::string &configPath, const std::string &libDir) :
        configPath(configPath), libDir(libDir) {
}

void SceneLoader::loadLibraries() {
    for (const auto &entry : fs::directory_iterator(libDir)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".so" || entry.path().extension() == ".dylib")) {
            try {
                auto lib = std::make_shared<DynamicLibrary>(entry.path().string());
                using GetNameFunc = const char* (*)();
                auto getName = lib->getSymbol<GetNameFunc>("getName");
                if (!getName) {
                    std::cerr << "Error: Unable to find 'getName' function in library " << entry.path() << std::endl;
                    continue;
                }
                std::string libName = getName();
                libraries.emplace_back(libName, lib);
            } catch (const std::runtime_error &e) {
                std::cerr << "Error loading library " << entry.path() << ": " << e.what() << std::endl;
            }
        }
    }
}

void SceneLoader::loadScene() {
    try {
        config.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file: " << configPath << std::endl;
        return;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return;
    }

    loadLibraries();

    for (const auto &lib : libraries) {
        std::string libName = std::get<0>(lib);
        std::shared_ptr<DynamicLibrary> libPtr = std::get<1>(lib);
        IEntity* (*createFunc)(const libconfig::Setting &setting) = nullptr;
        try {
            createFunc = reinterpret_cast<IEntity* (*)(const libconfig::Setting &setting)>(libPtr->getSymbol<IEntity *>("create"));
        } catch (const std::runtime_error &e) {
            std::cerr << "Error getting create function from library " << libName << ": " << e.what() << std::endl;
            continue;
        }

        if (config.exists(libName)) {
            const libconfig::Setting &settings = config.lookup(libName);
            if (libName.back() == 's') {
                for (int i = 0; i < settings.getLength(); ++i) {
                    try {
                        IEntity *entity = createFunc(settings[i]);
                        entities.push_back(entity);
                    } catch (const std::exception &e) {
                        std::cerr << "Error creating entity from library " << libName << ": " << e.what() << std::endl;
                        continue;
                    }
                }
            } else {
                try {
                    IEntity *entity = createFunc(settings);
                    entities.push_back(entity);
                } catch (const std::exception &e) {
                    std::cerr << "Error creating entity from library " << libName;
                    continue;
                }
            }
        }
    }
}

void SceneLoader::run() {
    ACamera *camera = nullptr;
    std::vector<IEntity *> spheres;

    for (auto &entity : entities) {
        if (entity->getType() == EntityType::Camera) {
            camera = dynamic_cast<ACamera *>(entity);
            continue;
        } else if (entity->getType() == EntityType::Primitive) {
            spheres.push_back(entity);
        }
    }

    if (!camera) {
        std::cerr << "Error: No camera found in scene" << std::endl;
        return;
    }

    float t = 0.0f;


    Image image(1920, 1080);

    std::vector<std::vector<Ray>> rays = camera->getRays();
    int x = 0;
    int y = 0;
    for (const auto &ray : rays) {
        for (const auto &r : ray) {
            float t = std::numeric_limits<float>::max();
            for (const auto &sphere : spheres) {
                if (sphere->intersect(r, t)) {
                    // set pix to blue
                    image.setPixel(y, x, Vec3(0.0f, 0.0f, 1.0f));
                    break;
                } else {
                    image.setPixel(y, x, Vec3(0.0f, 0.0f, 0.0f));
                }
            }
            y++;
        }
        y = 0;
        x++;
    }

    image.save("test.ppm");
}


