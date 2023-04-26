/*
** EPITECH PROJECT, 2023
** my_raytracer
** File description:
** BlueSkyBoxEntryPoint
*/

#include "BlueSkyBox.hpp"

extern "C" {
    ISkyBox* create() {
        return new RayTracer::Plugins::Skyboxes::BlueSkyBox();
    }

    void destroy(ISkyBox* ptr) {
        delete ptr;
    }

    const char* getPluginName() {
        return "BlueSkyBox";
    }
}