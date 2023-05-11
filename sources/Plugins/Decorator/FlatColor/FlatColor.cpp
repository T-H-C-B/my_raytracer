//
// Created by Theophilus Homawoo on 04/05/2023.
//

#include "FlatColor.hpp"
#include "ALight.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            FlatColor::FlatColor(const Shared::Vec3 &color, float absorption, float specularConstant, float shininess)
                    : _color(color), _absorption(absorption), _specularConstant(specularConstant), _shininess(shininess) {
            }

            void FlatColor::computeColor(RayTracer::Shared::Intersection &intersection,
                                         RayTracer::Shared::Ray const &ray,
                                         RayTracer::Shared::Vec3 &baseColor,
                                         std::unordered_map<RayTracer::Core::EntityType,
                                                 std::vector <RayTracer::Core::IEntity * >> entities,
                                         RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
                baseColor = _color * (1 - _absorption);

                RayTracer::Shared::Vec3 totalLightContribution(0, 0, 0);
                std::vector<RayTracer::Plugins::Lights::ALight *> lights;
                for (auto &lightEntity : entities[RayTracer::Core::EntityType::Light]) {
                    auto *light = static_cast<RayTracer::Plugins::Lights::ALight *>(lightEntity);
                    RayTracer::Shared::Vec3 lightColor = light->getColor();
                    float intensity = light->getIntensity();

                    RayTracer::Shared::Vec3 lightDirection = (light->getPosition() - intersection.point).normalize();

                    float dotProduct = std::max(0.0f, intersection.normal.dot(lightDirection));

                    totalLightContribution += (0.1f * dotProduct * intensity * lightColor) * (1 - _absorption);

                    RayTracer::Shared::Vec3 reflectionDirection = (2.0f * intersection.normal * dotProduct - lightDirection).normalize();
                    RayTracer::Shared::Vec3 viewDirection = (ray.getOrigin() - intersection.point).normalize();

                    float specDotProduct = std::max(0.0f, viewDirection.dot(reflectionDirection));
                    totalLightContribution += lightColor * _specularConstant * pow(specDotProduct, _shininess);
                }

                float maxLightContribution = 255.0f - _color.maxComponent();
                if (totalLightContribution.maxComponent() > maxLightContribution) {
                    totalLightContribution *= maxLightContribution / totalLightContribution.maxComponent();
                }

                baseColor += totalLightContribution;
            }
        } // RayTracer
    } // Plugins
} // Decorator