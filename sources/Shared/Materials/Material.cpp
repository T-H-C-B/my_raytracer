//
// Created by Clément Lagasse on 26/04/2023.
//

#include <iostream>
#include <random>
#include <limits>
#include "Parameters.hpp"
#include "Material.hpp"
#include "ALight.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"

RayTracer::Shared::Vec3 randomHemisphereDirection(const RayTracer::Shared::Vec3 &normal) {
    std::mt19937 gen(Parameters::getInstance().getSeed());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float u1 = dist(gen);
    float u2 = dist(gen);

    float r = sqrt(u1);
    float phi = 2.0f * M_PI * u2;

    float x = r * cos(phi);
    float y = r * sin(phi);
    float z = sqrt(1.0f - u1);

    RayTracer::Shared::Vec3 w = normal;
    RayTracer::Shared::Vec3 u = (std::abs(w.x) > 0.1f ? RayTracer::Shared::Vec3(0, 1, 0) : RayTracer::Shared::Vec3(1, 0, 0)).cross(w).normalize();
    RayTracer::Shared::Vec3 v = w.cross(u);

    return x * u + y * v + z * w;
}


namespace RayTracer {
    namespace Shared {

        void Material::addDecorator(RayTracer::Plugins::Decorators::IDecorator *decorator) {
            _decorators.push_back(decorator);
        }

        Vec3 Material::computeColor(Intersection &intersection, const Ray &ray,
                                    std::unordered_map<Core::EntityType, std::vector<RayTracer::Core::IEntity *>> &entities,
                                    RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
            Vec3 color = Vec3(255, 255, 255);
            for (auto &decorator : _decorators) {
                decorator->computeColor(intersection, ray, color, entities, SkyBox);
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
            float epsilon = 1e-3f;
            int numShadowRays = Parameters::getInstance().getNumShadowRays();
            Vec3 dropShadowColor(0.0f, 0.0f, 0.0f);

            for (const auto &light : lights) {
                if (light->inView(intersection.point)) {
                    float lightContribution = 0.0f;
                    float dropShadowFactor = 1.0f;

                    std::vector<Vec3> lightPositions = light->getJitteredPositions(numShadowRays);

                    for (const auto &lightPosition : lightPositions) {
                        Vec3 shadowRayOrigin = intersection.point + intersection.normal;
                        Ray shadowRay(shadowRayOrigin, (lightPosition - intersection.point));


                        bool isShadowed = false;
                        int tmp = 0;
                        for (auto &primitive : primitives) {
                            if (primitive == intersection.primitive) continue;

                            float t = std::numeric_limits<float>::max();
                            auto shadowIntersectionOpt = primitive->intersect(shadowRay, t);
                            if (shadowIntersectionOpt.has_value()) {
                                isShadowed = true;
                                break;
                            }
                        }

                        if (!isShadowed) {
                            Vec3 lightDirection = (lightPosition - intersection.point);
                            float dotProduct = std::max(0.0f, intersection.normal.dot(lightDirection));
                            lightContribution += dotProduct * light->getIntensity() / float(lights.size());
                        } else {
                            float shadowDistance = (shadowRayOrigin - intersection.point).length();
                            float maxShadowDistance = 10.0f;
                            dropShadowFactor = std::max(0.0f, 1.0f - (shadowDistance / maxShadowDistance));
                        }
                    }
                    shadowFactor += (lightContribution * dropShadowFactor) / numShadowRays;
                }
            }
            int numOcclusionRays = Parameters::getInstance().getNumOcclusionRays();
            float occlusionFactor = 0.0f;

            for (int i = 0; i < numOcclusionRays; i++) {
                Vec3 randomDirection = randomHemisphereDirection(intersection.normal);
                Ray occlusionRay(intersection.point + intersection.normal * epsilon, randomDirection.normalize());
                bool isOccluded = false;
                for (auto &primitive : primitives) {
                    float t;
                    auto occlusionIntersectionOpt = primitive->intersect(occlusionRay, t);
                    if (occlusionIntersectionOpt.has_value()) {
                        isOccluded = true;
                        break;
                    }
                }
                occlusionFactor += isOccluded ? 0.0f : 1.0f;
            }

            occlusionFactor /= numOcclusionRays;

            float ambientFactor = 0.3f * occlusionFactor;
            shadowFactor = shadowFactor + ambientFactor;
            shadowFactor = std::min(shadowFactor, 1.0f);
            return color * shadowFactor;
        }
    }
}
