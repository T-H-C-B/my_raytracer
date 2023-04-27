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
            std::vector<std::vector<RayTracer::Shared::Vec3>> getPixels() const { return pixels; };

        private:
            void setPixel(int x, int y, const RayTracer::Shared::Vec3& color);
            int width;
            int height;
            std::vector<std::vector<RayTracer::Shared::Vec3>>  pixels;
        };
    }
}
