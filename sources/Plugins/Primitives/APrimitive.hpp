//
// Created by Theophilus Homawoo on 19/04/2023.
//

#ifndef RAYTRACING_APRIMITIVE_HPP
#define RAYTRACING_APRIMITIVE_HPP

#include "IEntity.hpp"
#

class APrimitive : public IEntity {
public:
    IPrimitive() = default;
    virtual ~IPrimitive() = default;

    virtual bool intersect(const Ray& ray, float& t) const = 0;


    EntityType getType() const override {return EntityType::Primitive;}
};

#endif //RAYTRACING_APRIMITIVE_HPP
