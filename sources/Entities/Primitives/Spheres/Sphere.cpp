//
// Created by Theophilus Homawoo on 15/04/2023.
//

// Sphere.cpp
#include "Sphere.hpp"
#include <iostream>

namespace Primitives {

    Sphere::Sphere(const Vec3& center, float radius, const Vec3& color)
            : center(center), radius(radius), color(color) {
        std::cout << "Sphere created" << std::endl;
    }

    void Sphere::translate(const Vec3& translation) {
        center += translation;
    }

    EntityType Sphere::getType() const {
        return EntityType::Primitive;
    }

    void Sphere::rotate(const Vec3& rotation) {}

    void Sphere::scale(float scale) {
        radius *= scale;
    }

    bool Sphere::intersect(const Ray& ray, float& t) const {
        Vec3 oc = ray.getOrigin() - center;
        float a = ray.getDirection().dot(ray.getDirection());
        float b = 2.0f * oc.dot(ray.getDirection());
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            float temp = (-b - sqrt(discriminant)) / (2.0f * a);
            if (temp > 1e-4 && temp < t) {
                t = temp;
                return true;
            }
            temp = (-b + sqrt(discriminant)) / (2.0f * a);
            if (temp > 1e-4 && temp < t) {
                t = temp;
                return true;
            }
        }
        return false;
    }
}