/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CylinderEntryPoint
*/

#include <memory>
#include <libconfig.h++>
#include <iostream>
#include "Obj.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const libconfig::Setting &setting1)
    {
        RayTracer::Shared::Vec3 position;
        RayTracer::Shared::Vec3 rotation;
        std::string path;
        RayTracer::Core::IEntity* entity = nullptr;

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
                    throw RayTracer::Shared::ConfigError("OBJ", "Invalid position coordinates");
                }
                position = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("OBJ", "Missing position");
            }
        }
        if (setting1.exists("rotation")) {
            libconfig::Setting &setting = setting1.lookup("rotation");
            if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(setting.lookup("x"));
                    y = static_cast<int>(setting.lookup("y"));
                    z = static_cast<int>(setting.lookup("z"));
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
                path = static_cast<std::string>(setting1.lookup("path"));
            } catch (const libconfig::SettingTypeException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw RayTracer::Shared::ConfigError("OBJ", "Invalid path");
            }
        } else {
            throw RayTracer::Shared::ConfigError("OBJ", "Missing path");
        }
        entity = new RayTracer::Plugins::Primitives::Obj(position, rotation, path, 0.1);
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
