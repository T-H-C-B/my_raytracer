//
// Created by Bartosz on 4/30/23.
//

#include "PNGSkyBox.hpp"
#include "libconfig.h++"

extern "C" {
    RayTracer::Plugins::Skyboxes::ISkyBox* create(const libconfig::Setting &setting, const std::string &path) {
        return new RayTracer::Plugins::Skyboxes::PNGSkyBox(path);
    }

    void destroy(RayTracer::Plugins::Skyboxes::ISkyBox* skybox) {
        delete skybox;
    }

    const char* getName() {
        return "PNGSkyBox";
    }


}