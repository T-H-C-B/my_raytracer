//
// Created by Bartosz on 4/30/23.
//

#include "BlueSkyBox.hpp"
#include "PluginType.hpp"
#include "SettingWrapper.hpp"

extern "C" {
    RayTracer::Plugins::Skyboxes::ISkyBox* create(const RayTracer::Shared::SettingWrapper &setting) {
        return new RayTracer::Plugins::Skyboxes::BlueSkyBox();
    }

    void destroy(RayTracer::Plugins::Skyboxes::ISkyBox* skybox) {
        delete skybox;
    }

    const char* getName() {
        return "BlueSkyBox";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Skybox;
    }
}
