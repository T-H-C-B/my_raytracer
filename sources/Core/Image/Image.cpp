//
// Created by Theophilus Homawoo on 14/04/2023.
//

#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <optional>
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

void RayTracer::Core::Image::render(RayTracer::Core::Scene& scene) {

    RayTracer::Plugins::Cameras::ACamera *camera = static_cast<RayTracer::Plugins::Cameras::ACamera *>(scene.getActualCamera());

    std::vector<std::vector<RayTracer::Shared::Ray>> rays = camera->calculateRays();
    std::unordered_map<RayTracer::Core::EntityType, std::vector<IEntity *>> entities = scene.getEntities();
    int x = 0;
    int y = 0;

    for (auto & i : rays) {
        for (Shared::Ray ray : i) {
            std::unique_ptr<Shared::Intersection> intersection;
            Shared::Material *material;
            float minDistance = std::numeric_limits<float>::max();
            for (IEntity *primitive : entities[Core::EntityType::Primitive]) {
                auto *primitive_cast = dynamic_cast<Plugins::Primitives::IPrimitive *>(primitive);
                float t;
                std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> tmp = primitive_cast->intersect(ray, t);

                if (tmp && t < minDistance) {
                    minDistance = t;
                    intersection = std::move(tmp.value());
                    material = primitive_cast->getMaterial();
                }
            }

            Shared::Vec3 color = Shared::Vec3(0, 0, 0);
            if (intersection && intersection->hit) {
                color = material->computeColor(*intersection, ray, entities);
            } else {
                // Should set to skybox color
                color = Shared::Vec3(0, 0, 0);
            }
            setPixel(x, y, color);
            x++;
        }
        x = 0;
        y++;
    }
}

