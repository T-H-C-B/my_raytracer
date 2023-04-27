//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include <iostream>
#include "ACamera.hpp"
#include "BasicCamera.hpp"

RayTracer::Plugins::Cameras::BasicCamera::BasicCamera(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation)
: ACamera(position, rotation, RayTracer::Shared::Vec2(1920, 1080), 90.0f)
{
    /*
    RayTracer::Shared::Vec3 worldUp = RayTracer::Shared::Vec3(0, 0, 1);

    if (abs(direction.dot(worldUp)) == 1) {
        worldUp = RayTracer::Shared::Vec3(1, 0, 0); // Change worldUp to a non-parallel vector
    }

    RayTracer::Shared::Vec3 right = this->direction.cross(worldUp).normalize();
    RayTracer::Shared::Vec3 up = right.cross(this->direction);

    float aspectRatio = resolution.x / resolution.y;
    float _fovRadians = this->_fov * M_PI / 180.0f;
    float halfHeight = tan(_fovRadians / 2.0f);
    float halfWidth = aspectRatio * halfHeight;

    RayTracer::Shared::Vec3 w = direction.normalize();
    RayTracer::Shared::Vec3 u = w.cross(up).normalize();
    RayTracer::Shared::Vec3 v = w.cross(u).normalize(); // This line has been corrected

    for (int y = 0; y < (resolution.y); ++y) {
        std::vector<Ray> temp;
        for (int x = 0; x < (resolution.x); ++x) {
            float uScreen = -halfWidth + (2.0f * halfWidth * (x + 0.5f) / resolution.x);
            float vScreen = -halfHeight + (2.0f * halfHeight * (y + 0.5f) / resolution.y);

            RayTracer::Shared::Vec3 rayDirection = (w + u * uScreen +  v * vScreen).normalize();
            temp.emplace_back(position, rayDirection);
        }
        rays.emplace_back(temp);
    }
        */
    std::cout << "Basic Camera Created" << std::endl;
}

void RayTracer::Plugins::Cameras::BasicCamera::rotate(const RayTracer::Shared::Vec3 &rotation)
{
    // TODO
    calculateRays();
}

std::vector<std::vector<RayTracer::Shared::Ray>> RayTracer::Plugins::Cameras::BasicCamera::calculateRays() const
{
    /*
    RayTracer::Shared::Vec3 worldUp = RayTracer::Shared::Vec3(0, 0, 1);

    RayTracer::Shared::Vec3 right = direction.cross(worldUp).normalize();
    RayTracer::Shared::Vec3 up = right.cross(direction);

    float aspectRatio = resolution.x / resolution.y;
    float _fovRadians = this->_fov * M_PI / 180.0f;
    float halfHeight = tan(_fovRadians / 2.0f);
    float halfWidth = aspectRatio * halfHeight;

    RayTracer::Shared::Vec3 w = direction.normalize();
    RayTracer::Shared::Vec3 u = w.cross(up).normalize();
    RayTracer::Shared::Vec3 v = w.cross(u);

    for (int y = 0; y < (resolution.y); ++y) {
        for (int x = 0; x < (resolution.x); ++x) {
            float uScreen = -halfWidth + (2.0f * halfWidth * (x + 0.5f) / resolution.x);
            float vScreen = -halfHeight + (2.0f * halfHeight * (y + 0.5f) / resolution.y);

            RayTracer::Shared::Vec3 rayDirection = (w + u * uScreen +  v * vScreen).normalize();
            rays[y][x] = Ray(position, rayDirection);
        }
    }
     */
    return _rays;
}

RayTracer::Plugins::Cameras::BasicCamera::~BasicCamera() {
    for (auto &ray : _rays) {
        ray.clear();
    }
    _rays.clear();
}
