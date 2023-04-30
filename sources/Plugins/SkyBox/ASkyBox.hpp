//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ASKYBOX_HPP
#define MY_RAYTRACER_ASKYBOX_HPP

#include "Vec3.hpp"
#include "IEntity.hpp"
#include "ISkyBox.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class ASkyBox : public RayTracer::Plugins::Skyboxes::ISkyBox {
            public:
                ASkyBox() = default;


                virtual ~ASkyBox() = default;
                void translate(const RayTracer::Shared::Vec3 &translation) override {return;}
                void rotate(const RayTracer::Shared::Vec3 &rotation) override {return;}
                RayTracer::Core::EntityType getType() const override { return RayTracer::Core::EntityType::SkyBox; }
            };
        } // Skyboxes
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ASKYBOX_HPP
