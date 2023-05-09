//
// Created by Theophilus Homawoo on 30/04/2023.
//

#include <iostream>
#include "Plane.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "Vec3.hpp"
#include "SettingWrapper.hpp"

extern "C" {
RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
    int axisX;
    int axisY;
    int axisZ;
    int X;
    int Y;
    int Z;
    RayTracer::Shared::Vec3 color;

    if (setting.exists("axis")) {
        const RayTracer::Shared::SettingWrapper &settingaxis = setting.lookup<RayTracer::Shared::SettingWrapper>("axis");
        try {
            axisX = static_cast<int>(settingaxis.lookup<int>("x"));
            axisY = static_cast<int>(settingaxis.lookup<int>("y"));
            axisZ = static_cast<int>(settingaxis.lookup<int>("z"));
        } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw;
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing axis");
    }

    if (setting.exists("position")) {
        try {
            const RayTracer::Shared::SettingWrapper &settingposition = setting.lookup<RayTracer::Shared::SettingWrapper>("position");

            X = static_cast<int>(settingposition.lookup<int>("x"));
            Y = static_cast<int>(settingposition.lookup<int>("y"));
            Z = static_cast<int>(settingposition.lookup<int>("z"));
        } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw;
        }
    } else {
        throw RayTracer::Shared::ConfigError("Plane", "Missing position");
    }

    return new RayTracer::Plugins::Primitives::Plane(RayTracer::Shared::Vec3(float(axisX), float(axisY), float(axisZ)), RayTracer::Shared::Vec3(float(X), float(Y), float(Z)));
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
