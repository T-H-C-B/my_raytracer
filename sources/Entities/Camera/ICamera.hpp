//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_ICAMERA_HPP
#define RAYTRACING_ICAMERA_HPP

#include <memory>

#include "Ray.hpp"
#include "IEntity.hpp"

class ACamera : public IEntity {
public:
    virtual ~ACamera() = default;

    virtual std::vector<std::vector<Ray>> getRays() const = 0;
    EntityType getType() const override {return EntityType::Camera;}
};

#endif //RAYTRACING_ICAMERA_HPP
