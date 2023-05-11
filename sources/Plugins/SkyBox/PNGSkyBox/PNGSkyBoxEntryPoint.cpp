//
// Created by Bartosz on 4/30/23.
//

#include "PNGSkyBox.hpp"
#include "libconfig.h++"
#include "PluginType.hpp"
#include <iostream>
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Plugins::Skyboxes::ISkyBox* create(const RayTracer::Shared::SettingWrapper &setting) {
        try {
            std::string path = setting.lookup<std::string>("path");
            return new RayTracer::Plugins::Skyboxes::PNGSkyBox(path);
        } catch (const RayTracer::Shared::SettingWrapper::NotFoundException& ex) {
            std::cerr << "Error: " << ex.what() << " at " << ex.getPath() << std::endl;
            throw RayTracer::Shared::ConfigError("PNGSkyBox", "bad syntax");
        }
        return NULL;
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
