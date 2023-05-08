/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocGraphModule
*/

#include <iostream>
#include <fstream>
#include "EventManager.hpp"
#include "Image.hpp"
#include "PocGraphModule.hpp"

void RayTracer::Plugins::Graphics::PocGraphModule::update(RayTracer::Core::EventManager &eventManager)
{
    eventManager.addEvent(RayTracer::Core::EventType::QUIT);
}

void RayTracer::Plugins::Graphics::PocGraphModule::draw(RayTracer::Core::Image &image)
{
    std::ofstream outputFile("./tests/poc.ppm");
    auto pixels = image.getPixels();
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file: " <<  "poc.ppm.expected" << std::endl;
        return;
    }
    int height = static_cast<int>(pixels.size());
    int width = height > 0 ? static_cast<int>(pixels[0].size()) : 0;
    outputFile << "P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto pixel = pixels[i][j];
            int r = static_cast<int>(pixel.x);
            int g = static_cast<int>(pixel.y);
            int b = static_cast<int>(pixel.z);
            outputFile << r << " " << g << " " << b << "\n";
        }
    }
    outputFile.close();
}