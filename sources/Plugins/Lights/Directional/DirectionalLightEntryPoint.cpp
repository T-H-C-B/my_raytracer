//
// Created by Clément Lagasse on 02/05/2023.
//

#include <iostream>
#include <libconfig.h++>
#include "IEntity.hpp"
#include "ConfigError.hpp"
#include "DirectionalLight.hpp"
#include "PluginType.hpp"

extern "C" {

    RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 color;
        float intensity;

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
                throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("DirectionalLight", "Missing position");
        }

        if (setting.exists("intensity")) {
            const libconfig::Setting &intensitySetting = setting["intensity"];
            if (intensitySetting.exists("value")) {
                try {
                    intensity = static_cast<float>(intensitySetting.lookup("value"));
                } catch (const libconfig::SettingTypeException &ex) {
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
            const libconfig::Setting& colorSetting = setting["color"];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(colorSetting.lookup("r"));
                    g = static_cast<int>(colorSetting.lookup("g"));
                    b = static_cast<int>(colorSetting.lookup("b"));
                } catch (const libconfig::SettingTypeException& ex) {
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
        auto *light = new RayTracer::Plugins::Lights::DirectionalLight(position, RayTracer::Shared::Vec3(0.f, 0.f, 0.f), intensity, color);
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