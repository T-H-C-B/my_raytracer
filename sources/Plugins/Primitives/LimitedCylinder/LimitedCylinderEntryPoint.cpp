/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** LimitedCylinderEntryPoint
*/

#include <memory>
#include <iostream>
#include "LimitedCylinder.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        float radius;
        int height;
        RayTracer::Shared::Vec3 rotation;
        RayTracer::Shared::Vec3 color;

        if (setting.exists("position")){
            const RayTracer::Shared::SettingWrapper &settingA = setting.lookup<RayTracer::Shared::SettingWrapper>("position");
            if (settingA.exists("x") && settingA.exists("y") && settingA.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(settingA.lookup<int>("x"));
                    y = static_cast<int>(settingA.lookup<int>("y"));
                    z = static_cast<int>(settingA.lookup<int>("z"));
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
                int x, y, z;
                try {
                    x = static_cast<int>(settingB.lookup<int>("x"));
                    y = static_cast<int>(settingB.lookup<int>("y"));
                    z = static_cast<int>(settingB.lookup<int>("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    throw  RayTracer::Shared::ConfigError("Cylinder", "Unable to read coordinates");;
                }
                rotation = RayTracer::Shared::Vec3(x, y, z);
            }
        }
        if (setting.exists("height")) {
            try {
                height = static_cast<int>(setting.lookup<int>("height"));
            } catch (const libconfig::SettingTypeException& ex) {
                throw RayTracer::Shared::ConfigError("Cylinder", "Unable to read height value");
            }
        }
        return new RayTracer::Plugins::Primitives::LimitedCylinder(position, radius, rotation, height);
    }

    void destroy(RayTracer::Core::IEntity* cylinder) {
        delete cylinder;
    }

    const char *getName() {
        return "LimitedCylinder";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
