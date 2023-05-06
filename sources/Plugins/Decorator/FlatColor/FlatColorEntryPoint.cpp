//
// Created by Theophilus Homawoo on 04/05/2023.
//

#include <libconfig.h++>
#include <iostream>
#include "ConfigError.hpp"
#include "FlatColor.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Plugins::Decorators::IDecorator *create(const libconfig::Setting &setting) {
        RayTracer::Shared::Vec3 color;
        if (setting.exists("Color")) {
            const libconfig::Setting& colorSetting = setting[0];
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