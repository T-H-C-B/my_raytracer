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
RayTracer::Core::IEntity* create(const libconfig::Setting &setting) {
    std::string axis;
    int position;
    RayTracer::Shared::Vec3 color;

    if (setting.exists("axis")) {
        try {
            axis = static_cast<const char *>(setting.lookup("axis"));
        } catch (const libconfig::SettingTypeException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw;
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing axis");
    }

    if (setting.exists("position")) {
        try {
            position = static_cast<int>(setting.lookup("position"));
        } catch (const libconfig::SettingTypeException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw;
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing position");
    }

    //return new RayTracer::Plugins::Primitives::Plane(axis, float(position));
}

void destroy(RayTracer::Core::IEntity* plane) {
    delete plane;
}

const char *getName() {
    return "Planes";
}

RayTracer::Plugins::PluginType getType() {
    return RayTracer::Plugins::PluginType::Entity;
}
} // extern "C"
