/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocEntryPoint
*/

#include "PocGraphModule.hpp"

extern "C" {
    enum LibType { GRAPH = 0, GAME = 1, HOMESCREEN = 2};

    RayTracer::Plugins::IGraphModule *getGraphModule() {
        return new RayTracer::Plugins::PocGraphModule();
    }

    void destroyGraphModule(RayTracer::Plugins::IGraphModule *graphModule) {
        delete graphModule;
    }
}