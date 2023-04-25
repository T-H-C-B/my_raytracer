//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_AENTITY_HPP
#define MY_RAYTRACER_AENTITY_HPP

#include "Vec3.hpp"
#include "IEntity.hpp"

namespace RayTracer {
    namespace Entities {

        class AEntity : public IEntity {
            public:
                AEntity(Vec3 const &position, Vec3 const &rotation);
                ~AEntity() override = default;

                void translate(const Vec3& translation) override;
                void rotate(const Vec3& rotation) override;
            protected:
                Vec3 _position;
                Vec3 _rotation;
        };
    } // RayTracer
} // Entities

#endif //MY_RAYTRACER_AENTITY_HPP
