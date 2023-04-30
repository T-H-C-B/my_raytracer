/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CylinderEntryPoint
*/

#include "Cylinder.hpp"
#include <memory>
#include <libconfig.h++>
#include <iostream>
#include "Vec3.hpp"
#include "ConfigError.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
        RayTracer::Shared::Vec3 position;
        float height;
        float radius;
        RayTracer::Shared::Vec3 color;

        if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
            int x, y, z;
            try {
                x = static_cast<int>(setting.lookup("x"));
                y = static_cast<int>(setting.lookup("y"));
                z = static_cast<int>(setting.lookup("z"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }

            position = RayTracer::Shared::Vec3(x, y, z);
        } else {
            throw RayTracer::Shared::ConfigError("Cylinder", "Missing position coordinates");
        }

        if (setting.exists("radius")) {
            try {
                radius = static_cast<float>(setting.lookup("radius"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("Cylinder", "Missing radius value");
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
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("Cylinder", "Missing color");
        }

        return new RayTracer::Plugins::Primitives::Cylinder(position, radius, color);
    }

    void destroy(RayTracer::Core::IEntity* cylinder) {
        delete cylinder;
    }

    const char *getName() {
        return "Cylinders";
    }
}
