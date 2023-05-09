//
// Created by Theophilus Homawoo on 15/04/2023.
//

#include <iostream>
#include "Sphere.hpp"
#include "Material.hpp"
#include "Vec3.hpp"
#include "ConfigError.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting1) {
        RayTracer::Shared::Vec3 center;
        int radius;
        RayTracer::Shared::Vec3 color;
        RayTracer::Plugins::Primitives::Sphere *sphere;

        if (setting1.exists("position")) {
            const RayTracer::Shared::SettingWrapper &setting = setting1.lookup<RayTracer::Shared::SettingWrapper>("position");
            if (setting.exists("x") && setting.exists("y") && setting.exists("z")) {
                int x, y, z;
                try {
                    x = static_cast<int>(setting.lookup<int>("x"));
                    y = static_cast<int>(setting.lookup<int>("y"));
                    z = static_cast<int>(setting.lookup<int>("z"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("Sphere", "Invalid center coordinates");
                }

                center = RayTracer::Shared::Vec3(x, y, z);
            } else {
                throw RayTracer::Shared::ConfigError("Sphere", "Missing center coordinates");
            }
            if (setting.exists("r")) {
                try {
                    radius = static_cast<int>(setting.lookup<int>("r"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                    throw RayTracer::Shared::ConfigError("Sphere", "Invalid radius");
                }
            } else {
                throw RayTracer::Shared::ConfigError("Sphere", "Missing radius");
            }
            sphere = new RayTracer::Plugins::Primitives::Sphere(center, float(radius));
            return sphere;
        };
        //sphere->getMaterial()->addDecorator(RayTracer::Plugins::Primitives::MaterialDecoratorType::Color, color);
        return nullptr;
    }

    void destroy(RayTracer::Core::IEntity* sphere) {
        delete sphere;
    }

    const char *getName() {
        return "Sphere";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
