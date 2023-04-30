//
// Created by Theophilus Homawoo on 30/04/2023.
//

#include <libconfig.h++>
#include <iostream>
#include "Plane.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"

extern "C" {
RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
    std::string axis;
    int position;
    RayTracer::Shared::Vec3 color;

    if (setting.exists("axis")) {
        try {
            axis = static_cast<const char *>(setting.lookup("axis"));
        } catch (const libconfig::SettingTypeException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw;
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing axis");
    }

    if (setting.exists("position")) {
        try {
            position = static_cast<int>(setting.lookup("position"));
        } catch (const libconfig::SettingTypeException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw;
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing position");
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
            throw RayTracer::Shared::ConfigError("Plane", "Missing color values");
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing color");
    }

    return new RayTracer::Plugins::Primitives::Plane(axis, position, color);
}

void destroy(RayTracer::Core::IEntity* plane) {
    delete plane;
}

const char *getName() {
    return "Planes";
}
} // extern "C"
