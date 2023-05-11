#include "TransparencyDecorator.hpp"
#include "CustomError.hpp"
#include "APrimitive.hpp"
#include "Vec3.hpp"
#include "Material.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            TransparentDecorator::TransparentDecorator(float opacity, float indexOfRefraction)
                    : _opacity(opacity), _indexOfRefraction(indexOfRefraction){
                if (opacity < 0.0f || opacity > 1.0f) {
                    throw Shared::CustomError("TransparentDecorator: opacity must be between 0 and 1");
                }
            }

            void TransparentDecorator::computeColor(RayTracer::Shared::Intersection &intersection,
                                                    RayTracer::Shared::Ray const &ray,
                                                    RayTracer::Shared::Vec3 &baseColor,
                                                    std::unordered_map<RayTracer::Core::EntityType,
                                                    std::vector <RayTracer::Core::IEntity * >> entities,
                                                    RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
                RayTracer::Shared::Vec3 objectColor = baseColor;

                RayTracer::Shared::Ray refractedRay(intersection.point, ray.getDirection());
                RayTracer::Shared::Vec3 refractedColor(0.0f, 0.0f, 0.0f);

                float t = std::numeric_limits<float>::max();
                std::unique_ptr<RayTracer::Shared::Intersection> closestIntersection;

                std::vector<RayTracer::Plugins::Primitives::APrimitive *> primitives;
                for (auto &primitiveEntity: entities[Core::EntityType::Primitive]) {
                    primitives.push_back(
                            static_cast<RayTracer::Plugins::Primitives::APrimitive *>(primitiveEntity));
                }

                for (const auto &entity: primitives) {
                    if (entity == intersection.primitive) continue;
                    auto entityIntersectionOpt = entity->intersect(refractedRay, t);
                    if (entityIntersectionOpt.has_value()) {
                        closestIntersection = std::move(entityIntersectionOpt.value());
                    }
                }

                if (t != std::numeric_limits<float>::max()) {
                    RayTracer::Shared::Intersection localClosestIntersection = *closestIntersection;
                    RayTracer::Shared::Material *refractedMaterial = localClosestIntersection.primitive->getMaterial();
                    refractedColor = refractedMaterial->computeColor(localClosestIntersection, refractedRay, entities, SkyBox);
                }

                baseColor = objectColor * _opacity + refractedColor * (1.0f - _opacity);
            }
        } // RayTracer
    } // Plugins
} // Decorators
