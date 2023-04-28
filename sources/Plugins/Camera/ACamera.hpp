//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_ICAMERA_HPP
#define RAYTRACING_ICAMERA_HPP

#include <memory>
#include <vector>
#include "Ray.hpp"
#include "Vec2.hpp"
#include "ICamera.hpp"
#include "IEntity.hpp"
#include "AEntity.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Cameras {
            class ACamera : public RayTracer::Core::AEntity, public RayTracer::Plugins::Cameras::ICamera {
            public:

                ACamera(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, const RayTracer::Shared::Vec2 &resolution, float FOV)
                : RayTracer::Core::AEntity(position, rotation), _resolution(resolution), _fov(FOV), _direction(0, 0, 0)
                {};

                RayTracer::Core::EntityType getType() const override {return RayTracer::Core::EntityType::CAMERA;}


                void setFov(float FOV) override {_fov = FOV;};

                virtual ~ACamera() = default;
            protected:
                std::vector <std::vector<RayTracer::Shared::Ray>> _rays;
                float _fov;
                RayTracer::Shared::Vec2 _resolution;
                RayTracer::Shared::Vec3 _direction;
            };
        }
    }
}


#endif //RAYTRACING_ICAMERA_HPP
