//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_AENTITY_HPP
#define MY_RAYTRACER_AENTITY_HPP

#if defined(_WIN32)
#ifdef RAYTRACER_EXPORTS
        #define RAYTRACER_API __declspec(dllexport)
    #else
        #define RAYTRACER_API __declspec(dllimport)
    #endif
#else
#define RAYTRACER_API
#endif

#include "Vec3.hpp"
#include "IEntity.hpp"

namespace RayTracer {
    namespace Core {

    class AEntity : public RayTracer::Core::IEntity {
            public:
                AEntity(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation);
                ~AEntity() override = default;

                void translate(const RayTracer::Shared::Vec3 &translation) override;
                void rotate(const RayTracer::Shared::Vec3 &rotation) override;
                RayTracer::Shared::Vec3 _position;
            protected:
                RayTracer::Shared::Vec3 _rotation;
                RayTracer::Shared::Vec3 _direction;
        };
    } // RayTracer
} // Entities

#endif //MY_RAYTRACER_AENTITY_HPP
