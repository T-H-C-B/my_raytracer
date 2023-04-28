//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include "Image.hpp"

RayTracer::Core::Image::Image(int width, int height)
        : _width(width), _height(height), pixels(height, std::vector<RayTracer::Shared::Vec3>(width)) {}

void RayTracer::Core::Image::setPixel(int x, int y, const RayTracer::Shared::Vec3 &color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    pixels[y][x] = color;
}

void RayTracer::Core::Image::render(RayTracer::Core::Scene& scene) {
    // TO DO
}
