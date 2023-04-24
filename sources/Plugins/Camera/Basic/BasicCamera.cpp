//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include "BasicCamera.hpp"
#include <iostream>

BasicCamera::BasicCamera(const Vec3 &position, const Vec3 &direction, const Vec2 &resolution) {
    this->position = position;
    this->direction = (direction - position).normalize();

    this->resolution = resolution;
    this->FOV = 90.0f;

    Vec3 worldUp = Vec3(0, 0, 1);

    if (abs(direction.dot(worldUp)) == 1) {
        worldUp = Vec3(1, 0, 0); // Change worldUp to a non-parallel vector
    }

    Vec3 right = this->direction.cross(worldUp).normalize();
    Vec3 up = right.cross(this->direction);

    float aspectRatio = resolution.x / resolution.y;
    float fovRadians = this->FOV * M_PI / 180.0f;
    float halfHeight = tan(fovRadians / 2.0f);
    float halfWidth = aspectRatio * halfHeight;

    Vec3 w = direction.normalize();
    Vec3 u = w.cross(up).normalize();
    Vec3 v = w.cross(u).normalize(); // This line has been corrected

    for (int y = 0; y < (resolution.y); ++y) {
        std::vector<Ray> temp;
        for (int x = 0; x < (resolution.x); ++x) {
            float uScreen = -halfWidth + (2.0f * halfWidth * (x + 0.5f) / resolution.x);
            float vScreen = -halfHeight + (2.0f * halfHeight * (y + 0.5f) / resolution.y);

            Vec3 rayDirection = (w + u * uScreen +  v * vScreen).normalize();
            temp.emplace_back(position, rayDirection);
        }
        rays.emplace_back(temp);
    }

    std::cout << "Basic Camera Created" << std::endl;
}

bool BasicCamera::intersect(const Ray &ray, float &t) const {
    return false;
}

void BasicCamera::scale(float scale) {
    }

void BasicCamera::rotate(const Vec3 &rotation) {
    direction += rotation;
}

void BasicCamera::translate(const Vec3 &translation) {
    position += translation;
}

std::vector<std::vector<Ray>> BasicCamera::getRays() const {
    return rays;
}

void BasicCamera::setFOV(float FOV) {
    this->FOV = FOV;
    recalculateRays();
}

void BasicCamera::recalculateRays() {
    Vec3 worldUp = Vec3(0, 0, 1);

    Vec3 right = direction.cross(worldUp).normalize();
    Vec3 up = right.cross(direction);

    float aspectRatio = resolution.x / resolution.y;
    float fovRadians = this->FOV * M_PI / 180.0f;
    float halfHeight = tan(fovRadians / 2.0f);
    float halfWidth = aspectRatio * halfHeight;

    Vec3 w = direction.normalize();
    Vec3 u = w.cross(up).normalize();
    Vec3 v = w.cross(u);

    for (int y = 0; y < (resolution.y); ++y) {
        for (int x = 0; x < (resolution.x); ++x) {
            float uScreen = -halfWidth + (2.0f * halfWidth * (x + 0.5f) / resolution.x);
            float vScreen = -halfHeight + (2.0f * halfHeight * (y + 0.5f) / resolution.y);

            Vec3 rayDirection = (w + u * uScreen +  v * vScreen).normalize();
            rays[y][x] = Ray(position, rayDirection);
        }
    }
}

BasicCamera::~BasicCamera() {
    for (auto &ray : rays) {
        ray.clear();
    }
    rays.clear();
}
