//
// Created by Bartosz on 4/30/23.
//

#include "PNGSkyBox.hpp"
#include "libconfig.h++"
#include "PluginType.hpp"
#include "ConfigError.hpp"

extern "C" {
    RayTracer::Plugins::Skyboxes::ISkyBox* create(const libconfig::Setting &setting) {
        std::string path;
        setting.lookupValue("path", path);
        if (path.empty())
            throw RayTracer::Shared::ConfigError("PNGSkyBox", "Missing path");
        return new RayTracer::Plugins::Skyboxes::PNGSkyBox(path);
    }

    void destroy(RayTracer::Plugins::Skyboxes::ISkyBox* skybox) {
        delete skybox;
    }

    const char* getName() {
        return "PNGSkyBox";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Skybox;
    }


}