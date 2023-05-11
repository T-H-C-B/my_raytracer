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

std::vector<int> lastPrintedPercent;
std::mutex printMutex;

RayTracer::Core::Image::Image(int width, int height)
        : _width(width), _height(height), pixels(height, std::vector<RayTracer::Shared::Vec3>(width)) {
    unsigned int numThreads = std::thread::hardware_concurrency();
    lastPrintedPercent.resize(numThreads, -1);
}

void RayTracer::Core::Image::setPixel(int x, int y, const RayTracer::Shared::Vec3 &color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    pixels[y][x] = color;
}

void RayTracer::Core::Image::renderRow(int startY, int rowStep, RayTracer::Core::Scene& scene, const std::vector<std::vector<RayTracer::Shared::Ray>>& rays, const std::vector<Plugins::Primitives::IPrimitive *> &castedPrimitives, int step, int threadId) {
    for (int y = startY; y < _height; y += rowStep) {
        for (int x = 0; x < _width; x += step) {
            int rayX = x + step / 2;
            int rayY = y + step / 2;

            Shared::Ray ray = rays[rayY][rayX];
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
            RayTracer::Plugins::Skyboxes::ISkyBox *skyBox = scene.getActualSkyBox();
            Shared::Vec3 color;
            if (skyBox == nullptr) {
                color = intersection && intersection->hit ? material->computeColor(*intersection, ray, entities, scene.getActualSkyBox()) : Shared::Vec3(0, 0, 0);
            } else {
                color = intersection && intersection->hit ? material->computeColor(*intersection, ray, entities, scene.getActualSkyBox()) : skyBox->getColor(ray);
            }

            for (int offsetY = 0; offsetY < step && (y + offsetY) < _height; ++offsetY) {
                for (int offsetX = 0; offsetX < step && (x + offsetX) < _width; ++offsetX) {
                    setPixel(x + offsetX, y + offsetY, color);
                }
            }

            int percentComplete = static_cast<int>((static_cast<double>(x + y * _width) / (_width * _height)) * 100);

            if (percentComplete > lastPrintedPercent[threadId]) {
                lastPrintedPercent[threadId] = percentComplete;

                std::lock_guard<std::mutex> lock(printMutex);
                std::cout << "Thread " << threadId << " progress: " << percentComplete << "%" << std::endl;
            }
        }
    }
}


void RayTracer::Core::Image::render(RayTracer::Core::Scene& scene, float renderingPercentage) {
    if (renderingPercentage <= 0 || renderingPercentage > 1) {
        throw std::invalid_argument("renderingPercentage must be between 0 and 1");
    }

    int step = static_cast<int>(std::ceil(1 / renderingPercentage));

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
            int rowStep = numThreads * step;
            int startY = i * step;
            renderRow(startY, rowStep, scene, rays, castedPrimitives, step, i);
        });
    }

    for (std::thread &thread : threads) {
        thread.join();
    }
    applyBoxFilterAntiAliasing();
    lastPrintedPercent.clear();
}

void RayTracer::Core::Image::applyBoxFilterAntiAliasing() {
    std::vector<std::vector<RayTracer::Shared::Vec3>> filteredPixels(_height, std::vector<RayTracer::Shared::Vec3>(_width));
    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    auto applyBoxFilter = [&](int startY, int endY) {
        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < _width; ++x) {
                RayTracer::Shared::Vec3 sum(0, 0, 0);
                int count = 0;

                for (int offsetY = -1; offsetY <= 1; ++offsetY) {
                    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
                        int newY = y + offsetY;
                        int newX = x + offsetX;

                        if (newY >= 0 && newY < _height && newX >= 0 && newX < _width) {
                            sum += pixels[newY][newX];
                            count++;
                        }
                    }
                }

                filteredPixels[y][x] = sum / static_cast<float>(count);
            }
        }
    };

    int blockSize = _height / numThreads;
    for (unsigned int i = 0; i < numThreads; ++i) {
        int startY = i * blockSize;
        int endY = (i == numThreads - 1) ? _height : (i + 1) * blockSize;
        threads.emplace_back(applyBoxFilter, startY, endY);
    }

    for (std::thread &thread : threads) {
        thread.join();
    }

    pixels = std::move(filteredPixels);
}

