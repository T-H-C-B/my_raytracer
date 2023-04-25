//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_IMAGE_HPP
#define RAYTRACING_IMAGE_HPP


#pragma once

#include <string>
#include <vector>
#include "Vec3.hpp"

namespace RayTracer {
    namespace Shared {
        class Image {
        public:
            Image(int width, int height);

            void render(Raytracer::Core::Scene& scene);
            void save(const std::string& filename) const;

        private:
            void setPixel(int x, int y, const Vec3& color);
            int width;
            int height;
            std::vector<std::vector<Vec3> pixels>;
        };
    }
}




#endif //RAYTRACING_IMAGE_HPP
