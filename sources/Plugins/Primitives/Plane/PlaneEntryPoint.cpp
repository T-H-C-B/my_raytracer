//
// Created by Theophilus Homawoo on 30/04/2023.
//

#include "ConfigWrapper.hpp"
#include <iostream>
#include "Plane.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting1) {
        RayTracer::Shared::Vec3 normal;
        RayTracer::Shared::Vec3 position;

        if (setting1.exists("normal")) {
            const RayTracer::Shared::SettingWrapper &setting = setting1.lookup<RayTracer::Shared::SettingWrapper>("normal");
            if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
                float x, y, z;
                try {
                    x = static_cast<float>(setting.lookup<float>("x"));
                    y = static_cast<float>(setting.lookup<float>("y"));
                    z = static_cast<float>(setting.lookup<float>("z"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("Plane", "Invalid normal coordinates");
                }
                if (!(x == 0 || x == 1 || y == 0 || y == 1 || z == 0 || z == 1))
                    throw RayTracer::Shared::ConfigError("Plane", "Invalid normal coordinates");
                normal = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Plane", "Missing normal coordinates");
            }
        }
        if (setting1.exists("position")) {
            const RayTracer::Shared::SettingWrapper &setting = setting1.lookup<RayTracer::Shared::SettingWrapper>("position");
            if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
                float x, y, z;
                try {
                    x = static_cast<float>(setting.lookup<float>("x"));
                    y = static_cast<float>(setting.lookup<float>("y"));
                    z = static_cast<float>(setting.lookup<float>("z"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("Plane", "Invalid position coordinates");
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Plane", "Missing position");
            }
        }
        return new RayTracer::Plugins::Primitives::Plane(position, normal);
    }

    void destroy(RayTracer::Core::IEntity* plane) {
        delete plane;
    }

    const char *getName() {
        return "Plane";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}