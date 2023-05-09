/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SFMLEntryPoint
*/

#include "SFMLGraphModule.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Plugins::Graphics::IGraphModule *create(const RayTracer::Shared::SettingWrapper &setting) {
        return new RayTracer::Plugins::Graphics::SFMLGraphModule();
    }

    void destroyGraphModule(RayTracer::Plugins::Graphics::IGraphModule *graphModule) {
        delete graphModule;
    }

    const char* getName() {
        return "SFMLGraph";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Graphical;
    }
}
