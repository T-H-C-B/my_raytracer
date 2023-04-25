//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_ILIGHT_HPP
#define MY_RAYTRACER_ILIGHT_HPP

#include "IEntity.hpp"
#include "Vec3.hpp"

namespace RayTracer {
    namespace Entities {

        class ILight : public IEntity {

        public:

            virtual float getIntensity() const = 0;
            virtual Vec3f getPosition() const = 0;
            virtual bool inView(const Vec3f &point) const = 0;


            virtual ~ILight() = default;
        };

    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_ILIGHT_HPP
