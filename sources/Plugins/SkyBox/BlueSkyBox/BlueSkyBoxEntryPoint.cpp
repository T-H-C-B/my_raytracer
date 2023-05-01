//
// Created by Bartosz on 4/30/23.
//

#include "BlueSkyBox.hpp"
#include "libconfig.h++"

extern "C" {
    RayTracer::Plugins::Skyboxes::ISkyBox* create(const libconfig::Setting &setting) {
        return new RayTracer::Plugins::Skyboxes::BlueSkyBox();
    }

    void destroy(RayTracer::Plugins::Skyboxes::ISkyBox* skybox) {
        delete skybox;
    }

    const char* getName() {
        return "BlueSkyBox";
    }
}