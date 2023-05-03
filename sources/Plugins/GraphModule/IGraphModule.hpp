/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** IGraphModule
*/

#pragma once

#include "SceneManager.hpp"
#include "EventManager.hpp"
#include "Image.hpp"

namespace RayTracer {
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
