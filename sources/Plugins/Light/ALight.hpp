//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ALIGHT_HPP
#define MY_RAYTRACER_ALIGHT_HPP

namespace RayTracer {
    namespace Plugins {
        namespace Lights {
            class ALight {
            public:
                ALight() = default;

                float getIntensity() const;

                Vec3f getPosition() const;

                virtual ~ALight() = default;

            private:
                float intensity;
            };
        }
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ALIGHT_HPP
