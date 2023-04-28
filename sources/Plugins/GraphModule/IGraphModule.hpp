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
    namespace Core {
        class Image;
    }
}

namespace RayTracer {
    namespace Plugins {
        namespace Graphics {
            class IGraphModule {
            public:
                IGraphModule() = default;

                virtual ~IGraphModule() = default;

                virtual void update(RayTracer::Core::EventManager &eventManager,
                                    RayTracer::Core::Image) = 0;

            protected:
            private:
        };
        }
    } // namespace Plugins
} // namespace RayTracer
