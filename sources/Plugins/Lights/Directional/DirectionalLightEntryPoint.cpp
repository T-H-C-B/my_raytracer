//
// Created by Clément Lagasse on 02/05/2023.
//

#include "SettingWrapper.hpp"
#include <iostream>
#include "IEntity.hpp"
#include "ConfigError.hpp"
#include "DirectionalLight.hpp"
#include "PluginType.hpp"

extern "C" {

    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 color;
        RayTracer::Shared::Vec3 rotation;
        float intensity;

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
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position");
        }

        if (setting.exists("intensity")) {
            const RayTracer::Shared::SettingWrapper &intensitySetting = setting["intensity"];
            if (intensitySetting.exists("value")) {
                try {
                    intensity = static_cast<float>(intensitySetting.lookup<int>("value"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
            } else {
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing intensity value");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing intensity");
        }

        if (setting.exists("color")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting["color"];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(setting.lookup<int>("r"));
                    g = static_cast<int>(setting.lookup<int>("g"));
                    b = static_cast<int>(setting.lookup<int>("b"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                color = RayTracer::Shared::Vec3(r, g, b);
            } else {
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing color");
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
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing rotation values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing rotation");
        }
        auto *light = new RayTracer::Plugins::Lights::DirectionalLight(position, rotation, intensity, color);
        return light;
    }

    void destroy(RayTracer::Core::IEntity* entity) {
        delete entity;
    }

    const char* getName() {
        return "DirectionalLight";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
