// Created by Theophilus Homawoo on 16/04/2023.

#include <iostream>
#include <cmath>
#include "ACamera.hpp"
#include "BasicCamera.hpp"

RayTracer::Plugins::Cameras::BasicCamera::BasicCamera(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation)
        : ACamera(position, rotation, RayTracer::Shared::Vec2(1920, 1080), 90.0f)
{
    calculateRays();
    std::cout << "Basic Camera Created" << std::endl;
}

void RayTracer::Plugins::Cameras::BasicCamera::rotate(const RayTracer::Shared::Vec3 &rotation)
{
    RayTracer::Core::AEntity::rotate(rotation);
    calculateRays();
}

std::vector<std::vector<RayTracer::Shared::Ray>> RayTracer::Plugins::Cameras::BasicCamera::calculateRays()
{
    std::vector<std::vector<RayTracer::Shared::Ray>> rays;

    RayTracer::Shared::Vec3 worldUp = RayTracer::Shared::Vec3(0, 0, 1);

    if (abs(_direction.dot(worldUp)) == 1) {
        worldUp = RayTracer::Shared::Vec3(1, 0, 0);
    }

    RayTracer::Shared::Vec3 right = _direction.cross(worldUp).normalize();
    RayTracer::Shared::Vec3 up = right.cross(_direction);

    float aspectRatio = _resolution.x / _resolution.y;
    float fovRadians = _fov * M_PI / 180.0f;
    float halfHeight = tan(fovRadians / 2.0f);
    float halfWidth = aspectRatio * halfHeight;

    RayTracer::Shared::Vec3 w = _direction.normalize();
    RayTracer::Shared::Vec3 u = w.cross(up).normalize();
    RayTracer::Shared::Vec3 v = w.cross(u).normalize();

    for (int y = 0; y < (_resolution.y); ++y) {
        std::vector<RayTracer::Shared::Ray> temp;
        for (int x = 0; x < (_resolution.x); ++x) {
            float uScreen = -halfWidth + (2.0f * halfWidth * (x + 0.5f) / _resolution.x);
            float vScreen = -halfHeight + (2.0f * halfHeight * (y + 0.5f) / _resolution.y);

            RayTracer::Shared::Vec3 rayDirection = (w + u * uScreen + v * vScreen).normalize();
            temp.emplace_back(_position, rayDirection);
        }
        rays.emplace_back(temp);
    }

    return rays;
}

RayTracer::Plugins::Cameras::BasicCamera::~BasicCamera() {
    for (auto &ray : _rays) {
        ray.clear();
    }
    _rays.clear();
}
