//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Image.hpp"
#include <fstream>
#include <iostream>

RayTracer::Core::Image::Image(int width, int height)
        : width(width), height(height), pixels(height, std::vector<RayTracer::Shared::Vec3>(width)) {}

void RayTracer::Core::Image::setPixel(int x, int y, const RayTracer::Shared::Vec3 &color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    pixels[y][x] = color;
}

void RayTracer::Core::Image::render(RayTracer::Core::Scene& scene) {
    // TO DO
}
