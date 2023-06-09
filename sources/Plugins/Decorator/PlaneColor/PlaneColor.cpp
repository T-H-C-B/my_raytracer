//
// Created by Clement Lagasse on 07/05/2023.
//

#include <iostream>
#include "PlaneColor.hpp"

RayTracer::Plugins::Decorators::PlaneColor::PlaneColor(const RayTracer::Shared::Vec3 &checkBoardColor1, const RayTracer::Shared::Vec3 &checkBoardColor2)
    : _checkBoardColor1(checkBoardColor1), _checkBoardColor2(checkBoardColor2)
{
    std::cout << "PlaneColor constructor" << std::endl;
}

void RayTracer::Plugins::Decorators::PlaneColor::computeColor(RayTracer::Shared::Intersection &intersection,
                                                        const RayTracer::Shared::Ray &ray,
                                                        RayTracer::Shared::Vec3 &baseColor,
                                                        std::unordered_map<RayTracer::Core::EntityType,
                                                        std::vector<RayTracer::Core::IEntity *>>,
                                                        RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox)
{
    float checkerboardSize = 5.0;

    int x = static_cast<int>(std::floor(intersection.point.x / checkerboardSize));
    int z = static_cast<int>(std::floor(intersection.point.z / checkerboardSize));

    if ((x + z) % 2 == 0) {
        baseColor = _checkBoardColor1;
    } else {
        baseColor = _checkBoardColor2;
    }
}
