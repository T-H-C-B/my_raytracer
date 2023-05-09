//
// Created by Bartosz on 4/30/23.
//

#include "PNGSkyBox.hpp"
#include "libconfig.h++"
#include "PluginType.hpp"

extern "C" {
    RayTracer::Plugins::Skyboxes::ISkyBox* create(const libconfig::Setting &setting) {
        try {
            std::string path = setting.lookup("path");
            return new RayTracer::Plugins::Skyboxes::PNGSkyBox(path);
        } catch (const libconfig::SettingTypeException& ex) {
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