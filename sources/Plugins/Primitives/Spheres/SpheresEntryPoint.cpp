//
// Created by Theophilus Homawoo on 15/04/2023.
//

#include <memory>
#include <libconfig.h++>
#include <iostream>
#include "Sphere.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
        RayTracer::Shared::Vec3 center;
        int radius;
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

            center = RayTracer::Shared::Vec3(x, y, z);
        } else {
            throw RayTracer::Shared::ConfigError("Sphere", "Missing center coordinates");
        }

        if (setting.exists("r")) {
            try {
                radius = static_cast<int>(setting.lookup("r"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("Sphere", "Missing radius");
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
                throw RayTracer::Shared::ConfigError("Sphere", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("Sphere", "Missing color");
        }

        return new RayTracer::Plugins::Primitives::Sphere(center, radius, color);

    }

    void destroy(RayTracer::Core::IEntity* sphere) {
        delete sphere;
    }

    const char *getName() {
        return "Spheres";
    }
}


