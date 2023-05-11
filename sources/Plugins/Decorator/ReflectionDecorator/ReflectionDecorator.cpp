//
// Created by Theophilus Homawoo on 08/05/2023.
//

#include <limits>
#include <iostream>
#include <ALight.hpp>
#include "ReflectionDecorator.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            ReflectionDecorator::ReflectionDecorator(float reflectivity) : _reflectivity(reflectivity) {
                if (reflectivity < 0.0f || reflectivity > 1.0f) {
                    throw Shared::CustomError("ReflectionDecorator: reflectivity must be between 0 and 1");
                }
            }

            void ReflectionDecorator::computeColor(RayTracer::Shared::Intersection &intersection,
                                                   RayTracer::Shared::Ray const &ray,
                                                   RayTracer::Shared::Vec3 &baseColor,
                                                   std::unordered_map<RayTracer::Core::EntityType,
                                                   std::vector <RayTracer::Core::IEntity * >> entities,
                                                   RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
                RayTracer::Shared::Vec3 reflectionDirection = ray.getDirection() - 2.0f * (ray.getDirection().dot(intersection.normal)) * intersection.normal;
                RayTracer::Shared::Ray reflectionRay(intersection.point + intersection.normal * 1e-3f, reflectionDirection);

                float t = std::numeric_limits<float>::max();
                std::unique_ptr<RayTracer::Shared::Intersection> closestIntersection;

                std::vector<RayTracer::Plugins::Primitives::APrimitive *> primitives;
                for (auto &primitiveEntity : entities[Core::EntityType::Primitive]) {
                    primitives.push_back(static_cast<RayTracer::Plugins::Primitives::APrimitive *>(primitiveEntity));
                }


                for (const auto &entity : primitives) {
                    if (entity == intersection.primitive) continue;
                    auto entityIntersectionOpt = entity->intersect(reflectionRay, t);
                    if (entityIntersectionOpt.has_value()) {
                        closestIntersection = std::move(entityIntersectionOpt.value());
                    }
                }

                if (t != std::numeric_limits<float>::max()) {
                    RayTracer::Shared::Intersection localClosestIntersection = *closestIntersection;
                    RayTracer::Shared::Material *material = localClosestIntersection.primitive->getMaterial();
                    RayTracer::Shared::Vec3 reflectedColor = material->computeColor(localClosestIntersection, reflectionRay, entities, SkyBox);
                    baseColor = baseColor * (1.0f - _reflectivity) + reflectedColor * _reflectivity;
                } else {
                    if (SkyBox == nullptr) {
                        baseColor = baseColor * (1.0f - _reflectivity);
                        return;
                    }
                    RayTracer::Shared::Vec3 reflectedColor = SkyBox->getColor(reflectionRay);
                    baseColor = baseColor * (1.0f - _reflectivity) + reflectedColor * _reflectivity;
                }

                std::vector<RayTracer::Plugins::Lights::ALight *> lights;
                for (auto &lightEntity : entities[Core::EntityType::Light]) {
                    lights.push_back(static_cast<RayTracer::Plugins::Lights::ALight *>(lightEntity));
                }

                float shininess = 50.0f;
                Shared::Vec3 eyeDirection = (intersection.point - ray.getOrigin()).normalize();
                Shared::Vec3 totalSpecular = Shared::Vec3(0, 0, 0);

                for (const auto &light : lights) {
                    if (light->inView(intersection.point)) {
                        Shared::Vec3 lightColor = light->getColor();
                        Shared::Vec3 lightDirection = (light->getPosition() - intersection.point).normalize();
                        Shared::Vec3 reflectionDirection = (2 * intersection.normal * intersection.normal.dot(lightDirection) - lightDirection).normalize();

                        float spec = std::max(0.0f, eyeDirection.dot(reflectionDirection));
                        float specularFactor = pow(spec, shininess) * light->getIntensity() / float(lights.size());
                        totalSpecular += specularFactor * lightColor;
                    }
                }

                baseColor = baseColor + totalSpecular;
                if (baseColor.x > 255.0f) baseColor.x = 255.0f;
                if (baseColor.y > 255.0f) baseColor.y = 255.0f;
                if (baseColor.z > 255.0f) baseColor.z = 255.0f;
            }
        }
    }
}