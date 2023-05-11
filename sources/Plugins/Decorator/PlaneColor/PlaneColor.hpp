//
// Created by Clement Lagasse on 07/05/2023.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "IDecorator.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {
            class PlaneColor : public RayTracer::Plugins::Decorators::IDecorator {
                public:
                    PlaneColor(const RayTracer::Shared::Vec3 &checkBoardColor1, const RayTracer::Shared::Vec3 &checkBoardColor2);
                    ~PlaneColor() override = default;
                    void computeColor(RayTracer::Shared::Intersection &intersection,
                                      const RayTracer::Shared::Ray &ray,
                                      RayTracer::Shared::Vec3 &baseColor,
                                      std::unordered_map<RayTracer::Core::EntityType,
                                      std::vector<RayTracer::Core::IEntity *>>,
                                      RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) override;
                private:
                    Shared::Vec3 _checkBoardColor1;
                    Shared::Vec3 _checkBoardColor2;
            };

        } // RayTracer
    } // Plugins
} // Decorator
