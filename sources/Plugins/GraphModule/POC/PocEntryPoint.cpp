/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocEntryPoint
*/

#include "PocGraphModule.hpp"

extern "C" {
    enum LibType { ENTITY = 0, GRAPHMODULE = 1, DECORATOR = 2};

    RayTracer::Plugins::Graphics::IGraphModule *getGraphModule() {
        return new RayTracer::Plugins::Graphics::PocGraphModule();
    }

    void destroyGraphModule(RayTracer::Plugins::Graphics::IGraphModule *graphModule) {
        delete graphModule;
    }
}