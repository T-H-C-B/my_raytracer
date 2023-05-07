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
                SFMLGraphModule();

                ~SFMLGraphModule() override;

                void update(RayTracer::Core::EventManager &eventManager) override;
                void draw(RayTracer::Core::Image &image) override;

            protected:
            private:
                sf::RenderWindow m_window;
                bool _windowCreated;
                unsigned int _currentHeight;
                unsigned int _currentWidth;
                sf::Event _event;
                sf::Texture _texture;
            };
        }
    } // namespace Plugins
} // namespace RayTracer
