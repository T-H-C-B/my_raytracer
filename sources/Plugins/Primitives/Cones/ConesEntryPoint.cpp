#include "SettingWrapper.hpp"
/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ConesEntryPoint
*/

#include <memory>
#include <iostream>
#include "Cone.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 position;
        float radius;
        RayTracer::Shared::Vec3 color;

        if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
            int x, y, z;
            try {
                x = static_cast<int>(setting.lookup<int>("x"));
                y = static_cast<int>(setting.lookup<int>("y"));
                z = static_cast<int>(setting.lookup<int>("z"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }

            position = RayTracer::Shared::Vec3(x, y, z);
        } else {
            throw RayTracer::Shared::ConfigError("Cylinder", "Missing position coordinates");
        }

        if (setting.exists("radius")) {
            try {
                radius = static_cast<float>(setting.lookup<int>("radius"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw;
            }
        } else {
            throw RayTracer::Shared::ConfigError("Cylinder", "Missing radius value");
        }

        return new RayTracer::Plugins::Primitives::Cone(position, radius);
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
