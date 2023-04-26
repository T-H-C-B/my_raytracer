/*
** EPITECH PROJECT, 2023
** \
** File description:
** \
*/

#include "BlueSkyBox.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            BlueSkyBox::BlueSkyBox() {}

            Vec3f BlueSkyBox::getColor(const Ray &ray) const {
                return Vec3f(0.5, 0.7, 1);
            }
        }
    }
}