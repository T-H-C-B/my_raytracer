//
// Created by Theophilus Homawoo on 14/04/2023.
//

#pragma once

#include <string>
#include <vector>
#include "Vec3.hpp"
#include "Scene.hpp"

namespace RayTracer {
    namespace Core {
        class Image {
        public:
            Image(int width, int height);

            void render(RayTracer::Core::Scene& scene);
            void setWidth(int width) { _width = width; };
            void setHeight(int height) { _height = height; };
            [[nodiscard]] int getWidth() const { return _width; };
            [[nodiscard]] int getHeight() const { return _height; };
            [[nodiscard]] std::vector<std::vector<RayTracer::Shared::Vec3>> getPixels() const { return pixels; };

        private:
            void setPixel(int x, int y, const RayTracer::Shared::Vec3& color);
            int _width;
            int _height;
            std::vector<std::vector<RayTracer::Shared::Vec3>>  pixels;
            void renderRow(int y, RayTracer::Core::Scene& scene, const std::vector<std::vector<RayTracer::Shared::Ray>>& rays, const std::vector<Plugins::Primitives::IPrimitive *> &castedPrimitives);
            };
    }
}
