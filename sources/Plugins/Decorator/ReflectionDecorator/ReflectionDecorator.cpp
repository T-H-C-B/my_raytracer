//
// Created by Theophilus Homawoo on 08/05/2023.
//

#include <limits>
#include <iostream>
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
                                                           std::vector <RayTracer::Core::IEntity * >> entities) {
                RayTracer::Shared::Vec3 reflectionDirection = ray.getDirection() - 2.0f * (ray.getDirection().dot(intersection.normal)) * intersection.normal;
                RayTracer::Shared::Ray reflectionRay(intersection.point + intersection.normal * 1e-3f, reflectionDirection);

                float t = std::numeric_limits<float>::max();
                std::unique_ptr<RayTracer::Shared::Intersection> closestIntersection;

                std::vector<RayTracer::Plugins::Primitives::APrimitive *> primitives;
                for (auto &primitiveEntity : entities[Core::EntityType::Primitive]) {
                    primitives.push_back(static_cast<RayTracer::Plugins::Primitives::APrimitive *>(primitiveEntity));
                }


                for (const auto &entity : primitives) {

                    auto entityIntersectionOpt = entity->intersect(reflectionRay, t);
                    if (entityIntersectionOpt.has_value()) {
                        closestIntersection = std::move(entityIntersectionOpt.value());
                    }
                }

                if (t != std::numeric_limits<float>::max()) {
                    RayTracer::Shared::Intersection localClosestIntersection = *closestIntersection;
                    RayTracer::Shared::Material *material = localClosestIntersection.primitive->getMaterial();
                    RayTracer::Shared::Vec3 reflectedColor = material->computeColor(localClosestIntersection, reflectionRay, entities);
                    baseColor = baseColor * (1.0f - _reflectivity) + reflectedColor * _reflectivity;
                }
            }
        }
    }
}