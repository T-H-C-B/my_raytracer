#include <random>
#include <iostream>
#include "Material.hpp"
#include "ALight.hpp"
#include "IEntity.hpp"
#include "APrimitive.hpp"

RayTracer::Shared::Vec3 randomHemisphereDirection(const RayTracer::Shared::Vec3 &normal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    float u1 = dist(gen);
    float u2 = dist(gen);
    float z = std::abs(normal.z);
    float r = sqrt(std::max(0.0f, 1.0f - z * z));
    float phi = 2.0f * M_PI * u2;
    return RayTracer::Shared::Vec3(r * cos(phi), r * sin(phi), z);
}

namespace RayTracer {
    namespace Shared {

        void Material::addDecorator(RayTracer::Plugins::Decorators::IDecorator *decorator) {
            _decorators.push_back(decorator);
        }

        Vec3 Material::computeColor(Intersection &intersection, const Ray &ray,
                                    std::unordered_map<Core::EntityType, std::vector<RayTracer::Core::IEntity *>> &entities) {
            Vec3 color = Vec3(255, 255, 255);
            for (auto &decorator : _decorators) {
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
            float epsilon = 1e-3f;
            int numShadowRays = 5;

            for (const auto &light : lights) {
                if (light->inView(intersection.point)) {
                    float lightContribution = 0.0f;

                    for (int i = 0; i < numShadowRays; i++) {
                        Vec3 jitteredLightPos = light->getJitteredPosition();

                        Vec3 shadowRayOrigin = intersection.point + intersection.normal * epsilon;

                        Ray shadowRay(shadowRayOrigin, (jitteredLightPos - intersection.point).normalize());

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
                            Vec3 lightDirection = (jitteredLightPos - intersection.point).normalize();
                            float dotProduct = std::max(0.0f, intersection.normal.dot(lightDirection));
                            lightContribution += dotProduct * light->getIntensity() / float(lights.size());
                        }
                    }
                    shadowFactor += lightContribution / numShadowRays;
                }
            }
            int numOcclusionRays = 10;
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

            float ambientFactor = 0.1f * occlusionFactor;
            std::cout << occlusionFactor << std::endl;
            shadowFactor = shadowFactor + ambientFactor;
            shadowFactor = std::min(shadowFactor, 1.0f);
            return color * shadowFactor;
        }
    }
}
