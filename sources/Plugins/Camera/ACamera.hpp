//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_ICAMERA_HPP
#define RAYTRACING_ICAMERA_HPP

#include <memory>

#include "Ray.hpp"
#include "ICamera.hpp"
#include "IEntity.hpp"
#include <vector>

namespace RayTracer {
    namespace Plugins {
        class ACamera : public AEntity, public ICamera {
        public:
            virtual ~ACamera() = default;

            EntityType getType() const override;
            void setFOV(float FOV) override;

        protected:
            std::vector<std::vector<Ray>> rays;
            float FOV;
            Vec2 resolution;
            Vec3 direction;
        };
    }
}


#endif //RAYTRACING_ICAMERA_HPP
