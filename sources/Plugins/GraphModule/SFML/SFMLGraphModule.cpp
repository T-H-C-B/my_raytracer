/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SFMLGraphModule
*/

#include "SFMLGraphModule.hpp"
#include "Image.hpp"
#include "SFMLKeyEventMap.hpp"

RayTracer::Plugins::Graphics::SFMLGraphModule::SFMLGraphModule()
    : _windowCreated(false)
{
}

RayTracer::Plugins::Graphics::SFMLGraphModule::~SFMLGraphModule()
{
    m_window.close();
}

void RayTracer::Plugins::Graphics::SFMLGraphModule::update(RayTracer::Core::EventManager &eventManager)
{
    while (m_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            eventManager.addEvent(RayTracer::Core::EventType::QUIT);
            m_window.close();
        }

        if (_event.type == sf::Event::KeyPressed) {
            auto it = SFMLKeyEventMap.find(_event.key.code);
            if (it != SFMLKeyEventMap.end()) {
                RayTracer::Core::EventType eventType = it->second;
                eventManager.addEvent(eventType);
            }
        }
    }
}

void RayTracer::Plugins::Graphics::SFMLGraphModule::draw(RayTracer::Core::Image &image)
{
    if (!_windowCreated) {
        _currentHeight = image.getHeight();
        _currentWidth = image.getWidth();
        m_window.create(sf::VideoMode(_currentWidth, _currentHeight), "RayTracer");
        _windowCreated = true;
    }
    if (_currentHeight != image.getHeight() || _currentWidth != image.getWidth()) {
        _currentHeight = image.getHeight();
        _currentWidth = image.getWidth();
        m_window.close();
        m_window.create(sf::VideoMode(_currentWidth, _currentHeight), "RayTracer");
    }
    m_window.clear();
    auto pixels = image.getPixels();
    int height = static_cast<int>(pixels.size());
    int width = height > 0 ? static_cast<int>(pixels[0].size()) : 0;

    auto* pixelData = new sf::Uint8[width * height * 4];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto pixel = pixels[i][j];
            int r = static_cast<int>(pixel.x);
            int g = static_cast<int>(pixel.y);
            int b = static_cast<int>(pixel.z);
            int index = (i * width + j) * 4;
            pixelData[index + 0] = r;
            pixelData[index + 1] = g;
            pixelData[index + 2] = b;
            pixelData[index + 3] = 255;
        }
    }

    _texture.create(width, height);
    _texture.update(pixelData);
    sf::Sprite sprite(_texture);

    m_window.draw(sprite);
    m_window.display();

    delete[] pixelData;
}

