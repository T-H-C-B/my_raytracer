/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocGraphModule
*/

#include "PocGraphModule.hpp"

namespace RayTracer {
    namespace Plugins {
        PocGraphModule::PocGraphModule() {
        }

        PocGraphModule::~PocGraphModule()
        {
        }

        void PocGraphModule::update(RayTracer::Core::IEventManager &eventManager,
            RayTracer::Shared::Image &image)
        {
            std::ofstream outputFile("poc.ppm");
            auto pixels = image.getPixels();
            if (!outputFile.is_open()) {
                std::cerr << "Error: Unable to open the output file: " << filename << std::endl;
                eturn;
            }
            outputFile << "P3\n" << width << " " << height << "\n255\n";

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    const Vec3& color = pixels[y * width + x];
                    int r = static_cast<int>(255.0f * color.x);
                    int g = static_cast<int>(255.0f * color.y);
                    int b = static_cast<int>(255.0f * color.z);

                    outputFile << r << " " << g << " " << b << "\n";
                }
            }
            outputFile.close();
        }
    }
}