/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocEntryPoint
*/

#include "PocGraphModule.hpp"
#include "PluginType.hpp"
#include <libconfig.h++>

extern "C" {
    RayTracer::Plugins::Graphics::IGraphModule *create(const libconfig::Setting &setting) {
        return new RayTracer::Plugins::Graphics::PocGraphModule();
    }

    void destroyGraphModule(RayTracer::Plugins::Graphics::IGraphModule *graphModule) {
        delete graphModule;
    }

    const char* getName() {
        return "POCGraph";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Graphical;
    }
}