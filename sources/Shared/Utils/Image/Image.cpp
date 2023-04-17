//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Image.hpp"
#include <fstream>
#include <iostream>

Image::Image(int width, int height)
        : width(width), height(height), pixels(width * height) {}

void Image::setPixel(int x, int y, const Vec3& color) {
    pixels[y * width + x] = color;
}

void Image::save(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file: " << filename << std::endl;
        return;
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
