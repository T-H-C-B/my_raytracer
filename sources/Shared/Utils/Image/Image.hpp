//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_IMAGE_HPP
#define RAYTRACING_IMAGE_HPP


#pragma once

#include <string>
#include <vector>
#include "Vec3.hpp"

class Image {
    public:
        Image(int width, int height);

        void setPixel(int x, int y, const Vec3& color);
        void save(const std::string& filename) const;

    private:
        int width;
        int height;
        std::vector<Vec3> pixels;
};



#endif //RAYTRACING_IMAGE_HPP
