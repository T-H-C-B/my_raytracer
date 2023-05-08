//
// Created by Theophilus Homawoo on 30/04/2023.
//

#include <libconfig.h++>
#include <iostream>
#include "Plane.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"

extern "C" {
RayTracer::Core::IEntity* create(const libconfig::Setting &setting1) {
    RayTracer::Shared::Vec3 normal;
    RayTracer::Shared::Vec3 position;

    if (setting1.exists("normal")) {
        libconfig::Setting &setting = setting1.lookup("normal");
        if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
            int x, y, z;
            try {
                x = static_cast<int>(setting.lookup("x"));
                y = static_cast<int>(setting.lookup("y"));
                z = static_cast<int>(setting.lookup("z"));
            } catch (const libconfig::SettingTypeException &ex) {
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
        libconfig::Setting &setting = setting1.lookup("position");
        if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
            int x, y, z;
            try {
                x = static_cast<int>(setting.lookup("x"));
                y = static_cast<int>(setting.lookup("y"));
                z = static_cast<int>(setting.lookup("z"));
            } catch (const libconfig::SettingTypeException &ex) {
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
} // extern "C"
