//
// Created by Clément Lagasse on 26/04/2023.
//

#include <iostream>
#include <algorithm>
#include "Material.hpp"
#include "ALight.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"


void RayTracer::Shared::Material::addDecorator(RayTracer::Plugins::Decorators::IDecorator *decorator) {
    _decorators.push_back(decorator);
}

RayTracer::Shared::Vec3 RayTracer::Shared::Material::computeColor(Intersection &intersection, const Ray &ray, std::unordered_map<Core::EntityType, std::vector<RayTracer::Core::IEntity *>> &entities) {
    Vec3 color = Vec3(255, 255, 255);
    int x = 0;
    for (auto &decorator : _decorators) {
        x++;
        decorator->computeColor(intersection, ray, color, entities);
    }
    std::vector<RayTracer::Plugins::Lights::ALight *> lights;
    for (auto &lightEntity : entities[Core::EntityType::Light]) {
        lights.push_back(static_cast<RayTracer::Plugins::Lights::ALight *>(lightEntity));
    }
    std::vector<RayTracer::Plugins::Primitives::APrimitive *> primitives;
    for (auto &primitiveEntity : entities[Core::EntityType::Primitive]) {
        primitives.push_back(static_cast<RayTracer::Plugins::Primitives::APrimitive *>(primitiveEntity));
    }
    float shadowFactor = 0.0f;
    for (const auto &light : lights) {
        if (light->inView(intersection.point)) {
            Ray shadowRay(intersection.point, (light->getPosition() - intersection.point).normalize());
            bool isShadowed = false;
            for (auto &primitive : primitives) {
                float t;
                auto shadowIntersectionOpt = primitive->intersect(shadowRay, t);
                if (shadowIntersectionOpt.has_value()) {
                    isShadowed = true;
                    break;
                }
            }
            if (!isShadowed) {
                Vec3 lightDirection = (light->getPosition() - intersection.point).normalize();
                float dotProduct = std::max(0.0f, intersection.normal.dot(lightDirection));
                shadowFactor += dotProduct * light->getIntensity() / float(lights.size());
            }
        }
    }
    float ambientFactor = 0.1f;
    shadowFactor = shadowFactor + ambientFactor;
    shadowFactor = std::min(shadowFactor, 1.0f);

    color.x *= shadowFactor;
    color.y *= shadowFactor;
    color.z *= shadowFactor;

    return color;
}
