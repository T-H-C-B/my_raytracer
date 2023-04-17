//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_BASICCAMERA_HPP
#define RAYTRACING_BASICCAMERA_HPP

#include "IEntity.hpp"
#include "ICamera.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Vec2.hpp"
#include <vector>

class BasicCamera : public ACamera {
    public:
        BasicCamera(const Vec3& position, const Vec3& rotation, const Vec2& resolution);
        ~BasicCamera() override;

        void translate(const Vec3& translation) override;
        void rotate(const Vec3& rotation) override;
        void scale(float scale) override;
        bool intersect(const Ray& ray, float& t) const override;

        std::vector<std::vector<Ray>> getRays() const override;
        void setFOV(float FOV);
        EntityType getType() const override {return EntityType::Camera;}
    private:
        Vec3 position;
        Vec3 rotation;
        Vec2 resolution;
        Vec3 direction;
        float FOV;

        void recalculateRays();
        std::vector<std::vector<Ray>> rays;
};


#endif //RAYTRACING_BASICCAMERA_HPP
