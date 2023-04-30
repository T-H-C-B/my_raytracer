//
// Created by Bartosz on 4/30/23.
//

#pragma once

#include "ASkyBox.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class BlueSkyBox : public ASkyBox {
            public:
                BlueSkyBox() = default;
                ~BlueSkyBox() override = default;

                void rotate(const RayTracer::Shared::Vec3 &rotation) override { return;};
                RayTracer::Shared::Vec3 getColor(const RayTracer::Shared::Ray &ray) const override;
            };
        }
    } // RayTracer
} // Plugins