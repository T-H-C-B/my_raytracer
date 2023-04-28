/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocGraphModule
*/

#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "PocGraphModule.hpp"

RayTracer::Plugins::Graphics::PocGraphModule::PocGraphModule()
{
    // TODO
}

RayTracer::Plugins::Graphics::PocGraphModule::~PocGraphModule()
{
    // TODO
}

void RayTracer::Plugins::Graphics::PocGraphModule::update(RayTracer::Core::EventManager &eventManager,
                                                RayTracer::Core::Image &image)
{
    std::ofstream outputFile("poc.ppm");
    auto pixels = image.getPixels();
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file: " <<  "poc.ppm" << std::endl;
        return;
    }
    int height = static_cast<int>(pixels.size());
    int width = height > 0 ? static_cast<int>(pixels[0].size()) : 0;
    outputFile << "P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto pixel = pixels[i][j];
            int r = static_cast<int>(255.0f * pixel.x);
            int g = static_cast<int>(255.0f * pixel.y);
            int b = static_cast<int>(255.0f * pixel.z);
            outputFile << r << " " << g << " " << b << "\n";
        }
    }
    outputFile.close();
    // ajouter event quit
}