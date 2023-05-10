//
// Created by Clément Lagasse on 02/05/2023.
//

#include <iostream>
#include "IEntity.hpp"
#include "ConfigError.hpp"
#include "PointLight.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {

    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 color;
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
                throw RayTracer::Shared::ConfigError("PointLight", "Missing position values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("PointLight", "Missing position");
        }

        if (setting.exists("intensity")) {
            try {
                intensity = static_cast<float>(setting.lookup<float>("intensity"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("PointLight", "Missing intensity");
        }

        if (setting.exists("color")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting["color"];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(colorSetting.lookup<int>("r"));
                    g = static_cast<int>(colorSetting.lookup<int>("g"));
                    b = static_cast<int>(colorSetting.lookup<int>("b"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                color = RayTracer::Shared::Vec3(r, g, b);
            } else {
                throw RayTracer::Shared::ConfigError("PointLight", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("PointLight", "Missing color");
        }
        auto *light = new RayTracer::Plugins::Lights::PointLight(position, RayTracer::Shared::Vec3(0.f, 0.f, 0.f), intensity, color);
        return light;
    }

    void destroy(RayTracer::Core::IEntity* entity) {
        delete entity;
    }

    const char* getName() {
        return "PointLight";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
