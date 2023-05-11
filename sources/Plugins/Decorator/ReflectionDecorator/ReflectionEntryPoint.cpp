//
// Created by Théophilus Homawoo on 07/05/2023.
//

#include "SettingWrapper.hpp"
#include <iostream>
#include "ConfigError.hpp"
#include "ReflectionDecorator.hpp"
#include "PluginType.hpp"

extern "C" {
RayTracer::Plugins::Decorators::IDecorator *create(const RayTracer::Shared::SettingWrapper &setting) {
    float reflectivity;

    RayTracer::Shared::Vec3 color;
    if (setting.exists("Color")) {
        const RayTracer::Shared::SettingWrapper& colorSetting = setting[0];
        if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
            int r, g, b;
            try {
                r = static_cast<int>(colorSetting.lookup<int>("r"));
                g = static_cast<int>(colorSetting.lookup<int>("g"));
                b = static_cast<int>(colorSetting.lookup<int>("b"));
                reflectivity = static_cast<float>(colorSetting.lookup<float>("Reflectivity"));
            } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
                throw RayTracer::Shared::ConfigError("ReflectionDecorator", "Missing color values");
            }
            color = RayTracer::Shared::Vec3(r, g, b);
        } else {
            throw RayTracer::Shared::ConfigError("ReflectionDecorator", "Missing color values");
        }
    } else {
        throw RayTracer::Shared::ConfigError("ReflectionDecorator", "Missing Color");
    }

    //if (setting.exists("Reflectivity")) {
    //    try {
    //        reflectivity = static_cast<float>(setting.lookup("Reflectivity"));
    //    } catch (const libconfig::SettingTypeException& ex) {
    //        std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
    //        throw;
    //    }
    //} else {
    //    throw RayTracer::Shared::ConfigError("ReflectionDecorator", "Missing Reflectivity");
    //}
    return new RayTracer::Plugins::Decorators::ReflectionDecorator(reflectivity);
}

void destroy(RayTracer::Plugins::Decorators::IDecorator *decorator) {
    delete decorator;
}

const char* getName() {
    return "ReflectionDecorator";
}

RayTracer::Plugins::PluginType getType() {
    return RayTracer::Plugins::PluginType::Decorator;
}
}