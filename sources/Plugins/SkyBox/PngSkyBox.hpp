//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_PngSkyBox_HPP
#define MY_RAYTRACER_PngSkyBox_HPP

#include "ISkyBox.hpp"
#include <cmath>
#include <stdexcept>
#include <memory>
#include "stb_image.h"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class PngSkyBox : public ISkyBox {
                public:
                    PngSkyBox(const std::string &path);
                    virtual Vec3f getColor(const Ray &ray) const = 0;
                private:
                    std::unique_ptr<Vec3f[]> _image;
                    int _width;
                    int _height;
            };
        }
    } // RayTracer
} // Plugins

#endif //MY_RAYTRACER_PngSkyBox_HPP
