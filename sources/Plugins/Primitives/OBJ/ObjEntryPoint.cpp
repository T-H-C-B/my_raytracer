/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CylinderEntryPoint
*/

#include <libconfig.h++>
#include <iostream>
#include "Obj.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting1)
    {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 rotation;
        std::string path;
        RayTracer::Core::IEntity* entity = nullptr;

        if (setting1.exists("position")) {
            const RayTracer::Shared::SettingWrapper &setting = setting1.lookup<const RayTracer::Shared::SettingWrapper>("position");
            if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(setting.lookup<int>("x"));
                    y = static_cast<int>(setting.lookup<int>("y"));
                    z = static_cast<int>(setting.lookup<int>("z"));
                } catch (const libconfig::SettingTypeException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("OBJ", "Invalid position coordinates");
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("OBJ", "Missing position");
            }
        }
        if (setting1.exists("rotation")) {
            const RayTracer::Shared::SettingWrapper &setting = setting1.lookup<const RayTracer::Shared::SettingWrapper>("rotation");
            if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(setting.lookup<int>("x"));
                    y = static_cast<int>(setting.lookup<int>("y"));
                    z = static_cast<int>(setting.lookup<int>("z"));
                } catch (const libconfig::SettingTypeException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("OBJ", "Invalid rotation coordinates");
                }

                rotation = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("OBJ", "Missing rotation coordinates");
            }
        } else {
            throw RayTracer::Shared::ConfigError("OBJ", "Missing rotation");
        }
        if (setting1.exists("path")) {
            try {
                path = static_cast<std::string>(setting1.lookup<std::string>("path"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw RayTracer::Shared::ConfigError("OBJ", "Invalid path");
            }
        } else {
            throw RayTracer::Shared::ConfigError("OBJ", "Missing path");
        }
        entity = new RayTracer::Plugins::Primitives::Obj(position, rotation, path, 2);
        return entity;
    }

    void destroy(RayTracer::Core::IEntity* obj) {
        delete obj;
    }

    const char *getName() {
        return "OBJ";
    }


    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
