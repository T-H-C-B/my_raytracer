/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SFMLGraphModule
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Image.hpp"
#include "IGraphModule.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Graphics {
            class SFMLGraphModule : public Graphics::IGraphModule {
            public:
                SFMLGraphModule(unsigned int windowWidth, unsigned int windowHeight);

                ~SFMLGraphModule() override;

                void update(RayTracer::Core::EventManager &eventManager) override;
                void draw(RayTracer::Core::Image &image) override;

            protected:
            private:
                sf::RenderWindow m_window;
            };
        }
    } // namespace Plugins
} // namespace RayTracer
