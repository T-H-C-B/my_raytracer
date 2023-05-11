/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CylinderEntryPoint
*/

#include <memory>
#include <iostream>
#include "Cylinder.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        float radius;
        RayTracer::Shared::Vec3 rotation;
        RayTracer::Shared::Vec3 color;

        if (setting.exists("position")){
            const RayTracer::Shared::SettingWrapper &settingA = setting.lookup<RayTracer::Shared::SettingWrapper>("position");
            if (settingA.exists("x") && settingA.exists("y") && settingA.exists("z")) {
                float x, y, z;
                try {
                    x = static_cast<float>(settingA.lookup<float>("x"));
                    y = static_cast<float>(settingA.lookup<float>("y"));
                    z = static_cast<float>(settingA.lookup<float>("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    throw RayTracer::Shared::ConfigError("Cylinder", "Unable To read position coordinates");
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing position coordinates");
            }
            if (settingA.exists("radius")) {
                try {
                    radius = static_cast<float>(settingA.lookup<float>("radius"));
                } catch (const libconfig::SettingTypeException& ex) {
                    throw RayTracer::Shared::ConfigError("Cylinder", "Unable To read radius value");
                }
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing radius value");
            }
        }
        if (setting.exists("rotation")) {
           const RayTracer::Shared::SettingWrapper &settingB = setting.lookup<RayTracer::Shared::SettingWrapper>("rotation");
            if (settingB.exists("x") && settingB.exists("y") && settingB.exists("z")) {
                float x, y, z;
                try {
                    x = static_cast<float>(settingB.lookup<float>("x"));
                    y = static_cast<float>(settingB.lookup<float>("y"));
                    z = static_cast<float>(settingB.lookup<float>("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    throw RayTracer::Shared::ConfigError("Cylinder", "Unable To read rotation coordinates");
                }
                rotation = RayTracer::Shared::Vec3(x, y, z);
            }
        }
        return new RayTracer::Plugins::Primitives::Cylinder(position, radius, rotation);
    }

    void destroy(RayTracer::Core::IEntity* cylinder) {
        delete cylinder;
    }

    const char *getName() {
        return "Cylinder";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
