//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_BASICCAMERA_HPP
#define RAYTRACING_BASICCAMERA_HPP

#include "IEntity.hpp"
#include "ACamera.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Vec2.hpp"
#include <vector>

class BasicCamera : public ACamera {
    public:
        BasicCamera(const Vec3& position, const Vec3& rotation, const Vec2& resolution);
        ~BasicCamera() override;

        std::vector<std::vector<Ray>> calculateRays() const override;

    private:
        void recalculateRays();
        std::vector<std::vector<Ray>> rays;
};


#endif //RAYTRACING_BASICCAMERA_HPP
