//
// Created by Clément Lagasse on 24/04/2023.
//

#include "PngSkyBox.hpp"
#include "stb_image.h"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {

            PngSkyBox::PngSkyBox(const std::string &path)
                : _path(path) {
                int width, height, channels;
                unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
                if (!data) {
                    throw std::runtime_error("Failed to load image: " + path);
                }
                _image = std::make_unique<Vec3f[]>(width * height);

                for (int i = 0; i < width * height; ++i) {
                    _image[i] = Vec3f(
                        data[i * channels] / 255.0f,
                        data[i * channels + 1] / 255.0f,
                        data[i * channels + 2] / 255.0f
                    );
                }

                _width = width;
                _height = height;

                stbi_image_free(data);
            }

            Vec3f PngSkyBox::getColor(const Ray &ray) const {
                // Assuming the image is an equirectangular projection
                float u = 0.5 + atan2(ray.direction.z, ray.direction.x) / (2 * M_PI);
                float v = 0.5 - asin(ray.direction.y) / M_PI;

                int x = static_cast<int>(u * _width) % _width;
                int y = static_cast<int>(v * _height) % _height;

                return _image[y * _width + x];
            }

        }
    } // RayTracer
} // Plugins
