//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include "BasicCamera.hpp"
#include <iostream>
#include <libconfig.h++>
#include "ConfigError.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
        float fov;
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 rotation;
        RayTracer::Shared::Vec2 resolution;

        if (setting.exists("fieldOfView")) {
            try {
                fov = static_cast<float>(setting.lookup("fieldOfView"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("BasicCamera", "Missing FOV");
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
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("BasicCamera", "Missing position values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("BasicCamera", "Missing position");
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
                rotation = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("BasicCamera", "Missing rotation values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("BasicCamera", "Missing rotation");
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
                resolution = RayTracer::Shared::Vec2(x, y);
            } else {
                throw RayTracer::Shared::ConfigError("BasicCamera", "Missing resolution values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("BasicCamera", "Missing resolution");
        }

        auto* camera = new RayTracer::Plugins::Cameras::BasicCamera(position, rotation);
        camera->setFov(fov);
        return camera;
    }

    void destroy(RayTracer::Core::IEntity* entity) {
        delete entity;
    }

    const char* getName() {
        return "BasicCamera";
    }
}