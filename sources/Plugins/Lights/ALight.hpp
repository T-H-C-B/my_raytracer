//
// Created by Clément Lagasse on 24/04/2023.
//

#pragma once

#include "AEntity.hpp"
#include "ILight.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Lights {
            class ALight : public RayTracer::Core::AEntity, public RayTracer::Plugins::Lights::ILight{
            public:
                ALight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color)
                : AEntity(position, rotation), _intensity(intensity), _color(color) {}

                float getIntensity() const override {return _intensity;}

                RayTracer::Shared::Vec3 &getColor() override {return _color;}

                RayTracer::Shared::Vec3 &getPosition() override {return _position;}

                RayTracer::Shared::Vec3 &getDirection() override {return _direction;}

                RayTracer::Core::EntityType getType() const override {return RayTracer::Core::EntityType::Light;}

                ~ALight() override = default;

            protected:
                RayTracer::Shared::Vec3 _color;
                RayTracer::Shared::Vec3 _direction;
                float _intensity;
            };
        }
    } // RayTracer
} // Plugins

