//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include <iostream>
#include "ConfigError.hpp"
#include "BasicCamera.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        float fov;
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 rotation;
        RayTracer::Shared::Vec2 resolution;

        if (setting.exists("fieldOfView")) {
            try {
                fov = static_cast<float>(setting.lookup<float>("fieldOfView"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                throw RayTracer::Shared::ConfigError("BasicCamera", "Missing FOV");
            }
        } else {
            throw RayTracer::Shared::ConfigError("BasicCamera", "Missing FOV");
        }

        if (setting.exists("position")) {
            const RayTracer::Shared::SettingWrapper& positionSetting = setting["position"];
            if (positionSetting.exists("x") && positionSetting.exists("y") && positionSetting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(positionSetting.lookup<int>("x"));
                    y = static_cast<int>(positionSetting.lookup<int>("y"));
                    z = static_cast<int>(positionSetting.lookup<int>("z"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
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
            const RayTracer::Shared::SettingWrapper& rotationSetting = setting["rotation"];
            if (rotationSetting.exists("x") && rotationSetting.exists("y") && rotationSetting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(rotationSetting.lookup<int>("x"));
                    y = static_cast<int>(rotationSetting.lookup<int>("y"));
                    z = static_cast<int>(rotationSetting.lookup<int>("z"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
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
            const RayTracer::Shared::SettingWrapper& resolutionSetting = setting["resolution"];
            if (resolutionSetting.exists("x") && resolutionSetting.exists("y")) {
                int x, y;
                try {
                    x = static_cast<int>(resolutionSetting.lookup<int>("x"));
                    y = static_cast<int>(resolutionSetting.lookup<int>("y"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
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

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
