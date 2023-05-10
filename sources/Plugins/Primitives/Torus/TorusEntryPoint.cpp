/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** TorusEntryPoint
*/


#include <iostream>
#include "Torus.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 rotation;
        float majorRadius;
        float minorRadius;

        if (setting.exists("position")) {
            const RayTracer::Shared::SettingWrapper &settingA = setting.lookup<RayTracer::Shared::SettingWrapper>("position");
            if (settingA.exists("x") && settingA.exists("y") && settingA.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(settingA.lookup<int>("x"));
                    y = static_cast<int>(settingA.lookup<int>("y"));
                    z = static_cast<int>(settingA.lookup<int>("z"));
                } catch (const libconfig::SettingTypeException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw;
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Cylinder", "Missing position coordinates");
            }
        } else {
            throw RayTracer::Shared::ConfigError("Cylinder", "Missing position");
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

        if (setting.exists("majorRadius")) {
            try {
                majorRadius = static_cast<float>(setting.lookup<float>("majorRadius"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("Torus", "Missing major radius value");
        }

        if (setting.exists("minorRadius")) {
            try {
                minorRadius = static_cast<float>(setting.lookup<float>("minorRadius"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("Torus", "Missing minor radius value");
        }

        return new RayTracer::Plugins::Primitives::Torus(position, majorRadius, minorRadius, rotation);
    }

    void destroy(RayTracer::Core::IEntity* torus) {
        delete torus;
    }

    const char *getName() {
        return "Torus";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
