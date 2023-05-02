// PNGSkyBox.hpp
#pragma once

#include "ISkyBox.hpp"
#include <string>
#include <png.h>
#include <cmath>

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {
            class PNGSkyBox : public ISkyBox {
            public:
                PNGSkyBox(const std::string& filePath);
                virtual ~PNGSkyBox();

                void rotate(const RayTracer::Shared::Vec3 &rotation) override;
                RayTracer::Shared::Vec3 getColor(const RayTracer::Shared::Ray &ray) const override;

            private:
                png_bytep* row_pointers;
                int width, height;
                png_byte color_type;
                png_byte bit_depth;
                RayTracer::Shared::Vec3 rotation_data;

                void read_png_file(const std::string& filePath);
                RayTracer::Shared::Vec3 sample_color(const RayTracer::Shared::Vec3& direction) const;
                RayTracer::Shared::Vec3 apply_rotation(const RayTracer::Shared::Vec3& direction) const;

                RayTracer::Shared::Vec3 rotate_x(const RayTracer::Shared::Vec3& v, float angle) const;
                RayTracer::Shared::Vec3 rotate_y(const RayTracer::Shared::Vec3& v, float angle) const;
                RayTracer::Shared::Vec3 rotate_z(const RayTracer::Shared::Vec3& v, float angle) const;
            };
        }
    } // RayTracer
} // Plugins
