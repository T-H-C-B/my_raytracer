#include "SettingWrapper.hpp"
//
// Created by Theophilus Homawoo on 04/05/2023.
//

#include <iostream>
#include "ConfigError.hpp"
#include "FlatColor.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Plugins::Decorators::IDecorator *create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 color;
        if (setting.exists("Color")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting[0];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(colorSetting.lookup<int>("r"));
                    g = static_cast<int>(colorSetting.lookup<int>("g"));
                    b = static_cast<int>(colorSetting.lookup<int>("b"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    throw RayTracer::Shared::ConfigError("FlatColor", "Missing color values");
                }
                color = RayTracer::Shared::Vec3(r, g, b);
            } else {
                throw RayTracer::Shared::ConfigError("FlatColor", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("FlatColor", "Missing Color");
        }
        return new RayTracer::Plugins::Decorators::FlatColor(color);
    }

    void destroy(RayTracer::Plugins::Decorators::IDecorator *decorator) {
        delete decorator;
    }

    const char* getName() {
        return "FlatColor";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Decorator;
    }
}
