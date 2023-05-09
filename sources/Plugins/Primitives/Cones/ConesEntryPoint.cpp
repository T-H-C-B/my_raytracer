/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ConesEntryPoint
*/

#include <memory>
#include <libconfig.h++>
#include <iostream>
#include "Cone.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 color;
        RayTracer::Shared::Vec3 rotation;
        float radius;

        if (setting.exists("position")) {
            libconfig::Setting &settingA = setting.lookup("position");
            if (settingA.exists("x") && settingA.exists("y") && settingA.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(settingA.lookup("x"));
                    y = static_cast<int>(settingA.lookup("y"));
                    z = static_cast<int>(settingA.lookup("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing position coordinates");
            }
            if (settingA.exists("radius")) {
                try {
                    radius = static_cast<float>(settingA.lookup("radius"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing radius value");
            }
        }
        if (setting.exists("rotation")) {
            libconfig::Setting &settingB = setting.lookup("rotation");
            if (settingB.exists("x") && settingB.exists("y") && settingB.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(settingB.lookup("x"));
                    y = static_cast<int>(settingB.lookup("y"));
                    z = static_cast<int>(settingB.lookup("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cout << "Test" << std::endl;
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
                }
                rotation = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing rotation coordinates");
            }
        }
        return new RayTracer::Plugins::Primitives::Cone(position, radius, rotation);
    }

    void destroy(RayTracer::Core::IEntity* cone) {
        delete cone;
    }

    const char *getName() {
        return "Cone";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
