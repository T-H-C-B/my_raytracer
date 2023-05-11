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
                    throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position values");
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position");
        }
        if (setting.exists("intensity")) {
            try {
                intensity = static_cast<float>(setting.lookup<float>("intensity"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing intensity");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing intensity");
        }
        if (setting.exists("color")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting["color"];
            try {
                if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                    int r, g, b;
                    r = static_cast<int>(colorSetting.lookup<int>("r"));
                    g = static_cast<int>(colorSetting.lookup<int>("g"));
                    b = static_cast<int>(colorSetting.lookup<int>("b"));
                    color = RayTracer::Shared::Vec3(r, g, b);
                } else
                    throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing color values");
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing color");
        }
        if (setting.exists("direction")) {
            const RayTracer::Shared::SettingWrapper& rotationSetting = setting["direction"];
            if (rotationSetting.exists("x") && rotationSetting.exists("y") && rotationSetting.exists("z")) {
                float x, y, z;
                try {
                    x = static_cast<float>(rotationSetting.lookup<float>("x"));
                    y = static_cast<int>(rotationSetting.lookup<float>("y"));
                    z = static_cast<float>(rotationSetting.lookup<float>("z"));
                    if (x < 0 || x > 1 || y < 0 || y > 1 || z < 0 || z > 1)
                        throw RayTracer::Shared::ConfigError("DirectionalLight", "direction values must be between 0 and 1");
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing direction values");
                }
                rotation = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing direction values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing direction");
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
