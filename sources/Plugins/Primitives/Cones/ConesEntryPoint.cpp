/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ConesEntryPoint
*/

#include <iostream>
#include "Cone.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 color;
        RayTracer::Shared::Vec3 rotation;
        float radius;

        if (setting.exists("position")) {
            const RayTracer::Shared::SettingWrapper &settingA = setting.lookup<RayTracer::Shared::SettingWrapper>("position");
            if (settingA.exists("x") && settingA.exists("y") && settingA.exists("z")) {
                float x, y, z;
                try {
                    x = static_cast<float>(settingA.lookup<float>("x"));
                    y = static_cast<float>(settingA.lookup<float>("y"));
                    z = static_cast<float>(settingA.lookup<float>("z"));
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
                    radius = static_cast<float>(settingA.lookup<float>("radius"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing radius value");
            }
        }
        if (setting.exists("rotation")) {
            const RayTracer::Shared::SettingWrapper &settingB = setting.lookup<RayTracer::Shared::SettingWrapper>("rotation");
            if (settingB.exists("x") && settingB.exists("y") && settingB.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(settingB.lookup<int>("x"));
                    y = static_cast<int>(settingB.lookup<int>("y"));
                    z = static_cast<int>(settingB.lookup<int>("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                rotation = RayTracer::Shared::Vec3(x, y, z);
            }
        }
        if (setting.exists("radius")) {
            try {
                radius = static_cast<float>(setting.lookup<int>("radius"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("Cones", "Missing rotation coordinates");
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
