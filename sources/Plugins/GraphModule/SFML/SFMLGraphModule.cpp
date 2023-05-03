/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SFMLGraphModule
*/

#include "SFMLGraphModule.hpp"
#include "Image.hpp"

RayTracer::Plugins::Graphics::SFMLGraphModule::SFMLGraphModule(unsigned int windowWidth, unsigned int windowHeight)
    : m_window(sf::VideoMode(windowWidth, windowHeight), "RayTracer")
{
}

RayTracer::Plugins::Graphics::SFMLGraphModule::~SFMLGraphModule()
{
}

void RayTracer::Plugins::Graphics::SFMLGraphModule::update(RayTracer::Core::EventManager &eventManager)
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            eventManager.addEvent(RayTracer::Core::EventType::QUIT);
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            auto it = SFMLKeyEventMap.find(event.key.code);
            if (it != SFMLKeyEventMap.end()) {
                eventManager.addEvent(it->second);
            }
        }
    }
}

void RayTracer::Plugins::Graphics::SFMLGraphModule::draw(RayTracer::Core::Image &image)
{
    m_window.clear();
    auto pixels = image.getPixels();
    int height = static_cast<int>(pixels.size());
    int width = height > 0 ? static_cast<int>(pixels[0].size()) : 0;

    sf::Uint8* pixelData = new sf::Uint8[width * height * 4];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto pixel = pixels[i][j];
            int r = static_cast<int>(255.0f * pixel.x);
            int g = static_cast<int>(255.0f * pixel.y);
            int b = static_cast<int>(255.0f * pixel.z);
            int index = (i * width + j) * 4;
            pixelData[index + 0] = r;
            pixelData[index + 1] = g;
            pixelData[index + 2] = b;
            pixelData[index + 3] = 255;
        }
    }

    sf::Texture texture;
    texture.create(width, height);
    texture.update(pixelData);
    sf::Sprite sprite(texture);

    m_window.draw(sprite);
    m_window.display();

    delete[] pixelData;
}

