//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <optional>
#include <thread>
#include <mutex>
#include "Image.hpp"
#include "IPrimitive.hpp"
#include "Intersection.hpp"
#include "Material.hpp"
#include "ISkyBox.hpp"
#include "ACamera.hpp"

RayTracer::Core::Image::Image(int width, int height)
        : _width(width), _height(height), pixels(height, std::vector<RayTracer::Shared::Vec3>(width)) {}

void RayTracer::Core::Image::setPixel(int x, int y, const RayTracer::Shared::Vec3 &color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    pixels[y][x] = color;
}

void RayTracer::Core::Image::renderRow(int y, RayTracer::Core::Scene& scene, const std::vector<std::vector<RayTracer::Shared::Ray>>& rays, const std::vector<Plugins::Primitives::IPrimitive *> &castedPrimitives) {
    int x = 0;

    for (Shared::Ray ray : rays[y]) {
        std::unique_ptr<Shared::Intersection> intersection;
        Shared::Material *material;
        float minDistance = std::numeric_limits<float>::max();
        for (Plugins::Primitives::IPrimitive *primitive_cast : castedPrimitives) {
            float t = std::numeric_limits<float>::max();
            std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> tmp = primitive_cast->intersect(ray, t);

            if (tmp && t < minDistance) {
                minDistance = t;
                intersection = std::move(tmp.value());
                material = primitive_cast->getMaterial();
            }
        }
        std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> entities = scene.getEntities();

        Shared::Vec3 color = intersection && intersection->hit ? material->computeColor(*intersection, ray, entities) : Shared::Vec3(0, 0, 0);
        setPixel(x, y, color);
        x++;
    }
}

void RayTracer::Core::Image::render(RayTracer::Core::Scene& scene) {

    RayTracer::Plugins::Cameras::ACamera *camera = static_cast<RayTracer::Plugins::Cameras::ACamera *>(scene.getActualCamera());
    std::vector<std::vector<RayTracer::Shared::Ray>> rays = camera->calculateRays();
    std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> entities = scene.getEntities();
    std::vector<IEntity *> primitives = entities[Core::EntityType::Primitive];

    std::vector<Plugins::Primitives::IPrimitive *> castedPrimitives;
    castedPrimitives.reserve(primitives.size());
    for (IEntity *primitive : primitives) {
        castedPrimitives.push_back(dynamic_cast<Plugins::Primitives::IPrimitive *>(primitive));
    }

    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    for (unsigned int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&, i]() {
            for (int y = i; y < _height; y += numThreads) {
                renderRow(y, scene, rays, castedPrimitives);
            }
        });
    }

    for (std::thread &t : threads) {
        t.join();
    }
}


