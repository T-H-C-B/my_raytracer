//
// Created by Clément Lagasse on 09/05/2023.
//

#include <iostream>
#include "ALight.hpp"
#include "Vec3.hpp"
#include "MultipleDirectionalLight.hpp"

RayTracer::Plugins::Lights::MultipleDirectionalLight::MultipleDirectionalLight(const RayTracer::Shared::Vec3 &position, float intensity, const RayTracer::Shared::Vec3 &color)
: ALight(position, RayTracer::Shared::Vec3(), intensity, color)
{
    std::cout << "MultipleDirectionalLight constructor" << std::endl;
}

void RayTracer::Plugins::Lights::MultipleDirectionalLight::addLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &direction, float intensity, const RayTracer::Shared::Vec3 &color)
{
    std::unique_ptr<DirectionalLight> light = std::make_unique<DirectionalLight>(position, direction, intensity, color);
    light->setDirection(direction);
    lights.push_back(std::move(light));
}

bool RayTracer::Plugins::Lights::MultipleDirectionalLight::inView(const RayTracer::Shared::Vec3 &point) const {
    for (const auto &light : lights) {
        if (light->inView(point)) {
            return true;
        }
    }
    return false;
}

