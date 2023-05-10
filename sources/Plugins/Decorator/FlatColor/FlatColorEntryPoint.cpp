//
// Created by Theophilus Homawoo on 04/05/2023.
//

#include "ConfigError.hpp"
#include "FlatColor.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Plugins::Decorators::IDecorator *create(const RayTracer::Shared::SettingWrapper &setting) {
        RayTracer::Shared::Vec3 color;
        float absorption;
        float specularConstant;
        float shininess;
        if (setting.exists("Absorption")) {
            const RayTracer::Shared::SettingWrapper& absorptionSetting = setting["Absorption"];
            try {
                absorption = static_cast<float>(absorptionSetting.lookup<float>("value"));
            } catch (const libconfig::SettingTypeException& ex) {
                throw RayTracer::Shared::ConfigError("FlatColor", "Missing Absorption");
            }
        } else {
            throw RayTracer::Shared::ConfigError("FlatColor", "Missing Absorption");
        }
        if (setting.exists("Specular")) {
            const RayTracer::Shared::SettingWrapper& specularSetting = setting["Specular"];
            try {
                specularConstant = static_cast<float>(specularSetting.lookup<float>("value"));
            } catch (const libconfig::SettingTypeException& ex) {
                throw RayTracer::Shared::ConfigError("FlatColor", "Missing Specular");
            }
        } else {
            throw RayTracer::Shared::ConfigError("FlatColor", "Missing Specular");
        }
        if (setting.exists("Shininess")) {
            const RayTracer::Shared::SettingWrapper& shininessSetting = setting["Shininess"];
            try {
                shininess = static_cast<float>(shininessSetting.lookup<float>("value"));
            } catch (const libconfig::SettingTypeException& ex) {
                throw RayTracer::Shared::ConfigError("FlatColor", "Missing Shininess");
            }
        } else {
            throw RayTracer::Shared::ConfigError("FlatColor", "Missing Shininess");
        }
        if (setting.exists("Color")) {
            const RayTracer::Shared::SettingWrapper& colorSetting = setting["Color"];
            if (colorSetting.exists("r") && colorSetting.exists("g") && colorSetting.exists("b")) {
                int r, g, b;
                try {
                    r = static_cast<int>(colorSetting.lookup<int>("r"));
                    g = static_cast<int>(colorSetting.lookup<int>("g"));
                    b = static_cast<int>(colorSetting.lookup<int>("b"));
                } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
                    throw RayTracer::Shared::ConfigError("FlatColor", "Missing color values");
                }
                color = RayTracer::Shared::Vec3(r, g, b);
            } else {
                throw RayTracer::Shared::ConfigError("FlatColor", "Missing color values");
            }
        } else {
            throw RayTracer::Shared::ConfigError("FlatColor", "Missing Color");
        }
        return new RayTracer::Plugins::Decorators::FlatColor(color, absorption, specularConstant, shininess);
    }

    void destroy(RayTracer::Plugins::Decorators::IDecorator *decorator) {
        delete decorator;
    }

    const char* getName() {
        return "FlatColor";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Decorator;
    }
}
