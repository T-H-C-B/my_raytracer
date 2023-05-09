//
// Created by Bartosz Michalak on 07/05/2023.
//

#include "SettingWrapper.hpp"
#include <iostream>
#include "ConfigError.hpp"
#include "PNGDecorator.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Plugins::Decorators::IDecorator *create(const RayTracer::Shared::SettingWrapper &setting) {
        if (setting.exists("path"))
            return new RayTracer::Plugins::Decorators::PNGDecorator(setting.lookup<std::string>("path"));
        else
            throw RayTracer::Shared::ConfigError("PNGDecorator", "Missing path");
    }

    void destroy(RayTracer::Plugins::Decorators::IDecorator *decorator) {
        delete decorator;
    }

    const char* getName() {
        return "PNGDecorator";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Decorator;
    }
}