/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SFMLEntryPoint
*/

#include "SFMLGraphModule.hpp"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Plugins::Graphics::IGraphModule *getGraphModule(unsigned int windowWidth, unsigned int windowHeight) {
        return new RayTracer::Plugins::Graphics::SFMLGraphModule(windowWidth, windowHeight);
    }

    void destroyGraphModule(RayTracer::Plugins::Graphics::IGraphModule *graphModule) {
        delete graphModule;
    }

    const char* getName() {
        return "SFML";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Graphical;
    }
}