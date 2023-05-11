//
// Created by Clement Lagasse on 07/05/2023.
//

#include <libconfig.h++>
#include <iostream>
#include "ConfigError.hpp"
#include "PlaneColor.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Plugins::Decorators::IDecorator *create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 color1;
        RayTracer::Shared::Vec3 color2;

        if (setting.exists("Color1")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting[0];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(colorSetting.lookup<int>("r"));
                    g = static_cast<int>(colorSetting.lookup<int>("g"));
                    b = static_cast<int>(colorSetting.lookup<int>("b"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("PlaneColor", "Missing color values");

                }
                color1 = RayTracer::Shared::Vec3(r, g, b);
            } else {
                throw RayTracer::Shared::ConfigError("PlaneColor", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("PlaneColor", "Missing Color");
        }
        if (setting.exists("Color2")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting[1];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(colorSetting.lookup<int>("r"));
                    g = static_cast<int>(colorSetting.lookup<int>("g"));
                    b = static_cast<int>(colorSetting.lookup<int>("b"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("PlaneColor", "Missing color values");
                }
                color2 = RayTracer::Shared::Vec3(r, g, b);
            } else {
                throw RayTracer::Shared::ConfigError("PlaneColor", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("PlaneColor", "Missing Color");
        }
        return new RayTracer::Plugins::Decorators::PlaneColor(color1, color2);
    }

    void destroy(RayTracer::Plugins::Decorators::IDecorator *decorator) {
        delete decorator;
    }

    const char* getName() {
        return "PlaneColor";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Decorator;
    }
}