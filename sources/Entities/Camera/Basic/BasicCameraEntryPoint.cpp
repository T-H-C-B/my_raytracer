//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include "BasicCamera.hpp"
#include <iostream>
#include <libconfig.h++>
#include "ConfigError.hpp"

extern "C" {
    IEntity* create(const libconfig::Setting &setting) {
        float fov;
        Vec3 position;
        Vec3 rotation;
        Vec2 resolution;

        if (setting.exists("fieldOfView")) {
            try {
                fov = static_cast<float>(setting.lookup("fieldOfView"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw ConfigError("BasicCamera", "Missing FOV");
        }

        if (setting.exists("position")) {
            const libconfig::Setting& positionSetting = setting["position"];
            if (positionSetting.exists("x") && positionSetting.exists("y") && positionSetting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(positionSetting.lookup("x"));
                    y = static_cast<int>(positionSetting.lookup("y"));
                    z = static_cast<int>(positionSetting.lookup("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                position = Vec3(x, y, z);
            } else {
                throw ConfigError("BasicCamera", "Missing position values");
            }
        } else {
            throw ConfigError("BasicCamera", "Missing position");
        }

        if (setting.exists("rotation")) {
            const libconfig::Setting& rotationSetting = setting["rotation"];
            if (rotationSetting.exists("x") && rotationSetting.exists("y") && rotationSetting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(rotationSetting.lookup("x"));
                    y = static_cast<int>(rotationSetting.lookup("y"));
                    z = static_cast<int>(rotationSetting.lookup("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                rotation = Vec3(x, y, z);
            } else {
                throw ConfigError("BasicCamera", "Missing rotation values");
            }
        } else {
            throw ConfigError("BasicCamera", "Missing rotation");
        }

        if (setting.exists("resolution")) {
            const libconfig::Setting& resolutionSetting = setting["resolution"];
            if (resolutionSetting.exists("x") && resolutionSetting.exists("y")) {
                int x, y;
                try {
                    x = static_cast<int>(resolutionSetting.lookup("x"));
                    y = static_cast<int>(resolutionSetting.lookup("y"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                resolution = Vec2(x, y);
            } else {
                throw ConfigError("BasicCamera", "Missing resolution values");
            }
        } else {
            throw ConfigError("BasicCamera", "Missing resolution");
        }

        auto* camera = new BasicCamera(position, rotation, resolution);
        camera->setFOV(fov);
        return camera;
    }

    void destroy(IEntity* entity) {
        delete entity;
    }

    const char* getName() {
        return "BasicCamera";
    }
}