//
// Created by Theophilus Homawoo on 14/04/2023.
//

#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include "Vec3.hpp"

namespace RayTracer {
    class Ray {
    public:
        Ray(const Vec3& origin, const Vec3& direction);

        const Vec3& getOrigin() const;
        const Vec3 getDirection() const;

        Vec3 pointAt(float t) const;

    private:
        Vec3 origin;
        Vec3 direction;
    };
}


#endif //RAYTRACING_RAY_HPP
