//
// Created by Clément Lagasse on 09/05/2023.
//

#include "SettingWrapper.hpp"
#include <iostream>
#include "IEntity.hpp"
#include "ConfigError.hpp"
#include "MultipleDirectionalLight.hpp"
#include "PluginType.hpp"

extern "C" {

    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 color;
        RayTracer::Shared::Vec3 rotation;
        float intensity;
        RayTracer::Core::IEntity* light;

        if (setting.exists("position")) {
            const RayTracer::Shared::SettingWrapper& positionSetting = setting["position"];
            if (positionSetting.exists("x") && positionSetting.exists("y") && positionSetting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(positionSetting.lookup<int>("x"));
                    y = static_cast<int>(positionSetting.lookup<int>("y"));
                    z = static_cast<int>(positionSetting.lookup<int>("z"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing position values");
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing position values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing position");
        }
        if (setting.exists("intensity")) {
            try {
                intensity = static_cast<float>(setting.lookup<float>("intensity"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing intensity");
            }
        } else {
            throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing intensity");
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
                    throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing color values");
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing color values");
                }
        } else {
            throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing color");
        }
        light = new RayTracer::Plugins::Lights::MultipleDirectionalLight(position, intensity, color);
        RayTracer::Plugins::Lights::MultipleDirectionalLight *lightPlugin = static_cast<RayTracer::Plugins::Lights::MultipleDirectionalLight *>(light);
        if (setting.exists("directions")) {
            const RayTracer::Shared::SettingWrapper& directionsSetting = setting["directions"];
            if (!directionsSetting.isList() && !directionsSetting.isArray() && !directionsSetting.isGroup() || directionsSetting.getLength() == 0) {
                throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Invalid config type");
            }
            for (int i = 0; i < directionsSetting.getLength(); ++i) {
                const RayTracer::Shared::SettingWrapper &configItem = directionsSetting[i];
                if (configItem.exists("x") && configItem.exists("y") && configItem.exists("z")) {
                    int x, y, z;
                    try {
                        x = static_cast<int>(configItem.lookup<int>("x"));
                        y = static_cast<int>(configItem.lookup<int>("y"));
                        z = static_cast<int>(configItem.lookup<int>("z"));
                    } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                        throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing direction values");
                    }
                    rotation = RayTracer::Shared::Vec3(x, y, z);
                    std::cout << "Adding light with rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
                    lightPlugin->addLight(position, rotation, intensity, color);
                } else {
                    throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing direction values");
                }
            }
        } else {
            delete light;
            throw RayTracer::Shared::ConfigError("MultipleDirectionalLight", "Missing directions");
        }
        return light;
    }

    void destroy(RayTracer::Core::IEntity* entity) {
        delete entity;
    }

    const char* getName() {
        return "MultipleDirectionalLight";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
