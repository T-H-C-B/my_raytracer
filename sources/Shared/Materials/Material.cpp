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

RayTracer::Shared::Vec3 RayTracer::Shared::Material::rgbToHsv(const RayTracer::Shared::Vec3 &rgbColor)
{
    float r = rgbColor.x / 255.0f;
    float g = rgbColor.y / 255.0f;
    float b = rgbColor.z / 255.0f;

    float maxVal = std::max({r, g, b});
    float minVal = std::min({r, g, b});
    float delta = maxVal - minVal;

    float h, s, v;
    v = maxVal;

    if (delta == 0) {
        h = 0;
        s = 0;
    } else {
        s = delta / maxVal;
        if (r == maxVal) {
            h = (g - b) / delta;
        } else if (g == maxVal) {
            h = 2 + (b - r) / delta;
        } else {
            h = 4 + (r - g) / delta;
        }
        h *= 60;
        if (h < 0) {
            h += 360;
        }
    }
    return RayTracer::Shared::Vec3(h, s * 100, v * 100);
}

RayTracer::Shared::Vec3 RayTracer::Shared::Material::hsvToRgb(const Vec3 &hsvColor)
{
    float h = hsvColor.x;
    float s = hsvColor.y / 100;
    float v = hsvColor.z / 100;

    float r, g, b;
    int i = static_cast<int>(h / 60) % 6;
    float f = h / 60 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i) {
        case 0:
            r = v, g = t, b = p;
            break;
        case 1:
            r = q, g = v, b = p;
            break;
        case 2:
            r = p, g = v, b = t;
            break;
        case 3:
            r = p, g = q, b = v;
            break;
        case 4:
            r = t, g = p, b = v;
            break;
        case 5:
        default:
            r = v, g = p, b = q;
            break;
    }

    return Vec3(r * 255, g * 255, b * 255);
}

RayTracer::Shared::Vec3 RayTracer::Shared::Material::computeColor(Intersection &intersection, const Ray &ray, std::unordered_map<Core::EntityType, std::vector<RayTracer::Core::IEntity *>> &entities) {
    Vec3 color = Vec3(255, 255, 255);
    int x = 0;
    for (auto &decorator : _decorators) {
        x++;
        printf("decorator %d\n", x);
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

    // Multiply each component of the color by the shadow factor
    color.x *= shadowFactor;
    color.y *= shadowFactor;
    color.z *= shadowFactor;

    return color;
}
