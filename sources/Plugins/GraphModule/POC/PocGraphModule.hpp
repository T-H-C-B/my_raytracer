/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocGraphModule
*/

#pragma once

#include "Image.hpp"
#include "IGraphModule.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Graphics {
            class PocGraphModule : public Graphics::IGraphModule {
            public:
                PocGraphModule();

                ~PocGraphModule() override;

                void update(RayTracer::Core::EventManager &eventManager,
                            RayTracer::Core::Image &image) override;

            protected:
            private:
            };
        }
    } // namespace Plugins
} // namespace RayTracer

