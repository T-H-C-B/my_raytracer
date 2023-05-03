/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** IGraphModule
*/

#pragma once

#include "EventManager.hpp"

namespace RayTracer {
    namespace Core {
        class Image;
    }
    namespace Plugins {
        namespace Graphics {
            class IGraphModule {
            public:
                IGraphModule() = default;

                virtual ~IGraphModule() = default;
                virtual void update(RayTracer::Core::EventManager &eventManager) = 0;
                virtual void draw(RayTracer::Core::Image &image) = 0;

            protected:
            private:
        };
        }
    } // namespace Plugins
} // namespace RayTracer
