//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_BASICCAMERA_HPP
#define RAYTRACING_BASICCAMERA_HPP

#include "IEntity.hpp"
#include "ACamera.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Vec2.hpp"
#include <vector>

namespace RayTracer {
    namespace Plugins {

        namespace Cameras {
            class BasicCamera : public ACamera {
            public:
                BasicCamera(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation);

                void rotate(const RayTracer::Shared::Vec3 &rotation) override;
                ~BasicCamera() override;

                std::vector <std::vector<RayTracer::Shared::Ray>> calculateRays() const override;
            };
        }
    }
}

#endif //RAYTRACING_BASICCAMERA_HPP
