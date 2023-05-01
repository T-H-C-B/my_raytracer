// PNGSkyBox.cpp
#include "PNGSkyBox.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace RayTracer {
    namespace Plugins {
        namespace Skyboxes {

            PNGSkyBox::PNGSkyBox(const std::string &filePath) {
                read_png_file(filePath);
            }

            PNGSkyBox::~PNGSkyBox() {
                for (int y = 0; y < height; y++) {
                    free(row_pointers[y]);
                }
                free(row_pointers);
            }

            void PNGSkyBox::rotate(const RayTracer::Shared::Vec3 &rotation) {
                rotation_data += rotation;
            }

            RayTracer::Shared::Vec3 PNGSkyBox::getColor(const RayTracer::Shared::Ray &ray) const {
                RayTracer::Shared::Vec3 rotated_direction = apply_rotation(ray.getDirection());
                return sample_color(rotated_direction);
            }

            RayTracer::Shared::Vec3 rotate_x(const RayTracer::Shared::Vec3 &v, float angle) {
                float c = cos(angle);
                float s = sin(angle);
                return RayTracer::Shared::Vec3(v.x, c * v.y - s * v.z, s * v.y + c * v.z);
            }

            RayTracer::Shared::Vec3 rotate_y(const RayTracer::Shared::Vec3 &v, float angle) {
                float c = cos(angle);
                float s = sin(angle);
                return RayTracer::Shared::Vec3(c * v.x + s * v.z, v.y, -s * v.x + c * v.z);
            }

            RayTracer::Shared::Vec3 rotate_z(const RayTracer::Shared::Vec3 &v, float angle) {
                float c = cos(angle);
                float s = sin(angle);
                return RayTracer::Shared::Vec3(c * v.x - s * v.y, s * v.x + c * v.y, v.z);
            }

            RayTracer::Shared::Vec3 PNGSkyBox::apply_rotation(const RayTracer::Shared::Vec3 &direction) const {
                RayTracer::Shared::Vec3 rotation_radians = rotation_data * (3.14159265f / 180.0f);

                RayTracer::Shared::Vec3 rotated = rotate_x(direction, rotation_radians.x);
                rotated = rotate_y(rotated, rotation_radians.y);
                rotated = rotate_z(rotated, rotation_radians.z);

                return rotated;
            }

            void PNGSkyBox::read_png_file(const std::string &filePath) {
                FILE *fp = fopen(filePath.c_str(), "rb");

                if (!fp) {
                    throw std::runtime_error("Error: Unable to open file " + filePath);
                }

                png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
                if (!png) {
                    throw std::runtime_error("Error: Failed to create read struct for png.");
                }

                png_infop info = png_create_info_struct(png);
                if (!info) {
                    png_destroy_read_struct(&png, NULL, NULL);
                    throw std::runtime_error("Error: Failed to create info struct for png.");
                }

                if (setjmp(png_jmpbuf(png))) {
                    png_destroy_read_struct(&png, &info, NULL);
                    fclose(fp);
                    throw std::runtime_error("Error: Failed to read png file.");
                }

                png_init_io(png, fp);
                png_read_info(png, info);

                width = png_get_image_width(png, info);
                height = png_get_image_height(png, info);
                color_type = png_get_color_type(png, info);
                bit_depth = png_get_bit_depth(png, info);


                if (bit_depth == 16) {
                    png_set_strip_16(png);
                }

                if (color_type == PNG_COLOR_TYPE_PALETTE) {
                    png_set_palette_to_rgb(png);
                }

                if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
                    png_set_expand_gray_1_2_4_to_8(png);
                }

                if (png_get_valid(png, info, PNG_INFO_tRNS)) {
                    png_set_tRNS_to_alpha(png);
                }

                if (color_type == PNG_COLOR_TYPE_RGB ||
                    color_type == PNG_COLOR_TYPE_GRAY ||
                    color_type == PNG_COLOR_TYPE_PALETTE) {
                    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
                }

                if (color_type == PNG_COLOR_TYPE_GRAY ||
                    color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
                    png_set_gray_to_rgb(png);
                }

                png_read_update_info(png, info);

                row_pointers = (png_bytep *)
                        malloc(sizeof(png_bytep) * height);
                for (int y = 0; y < height; y++) {
                    row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(png, info));
                }

                png_read_image(png, row_pointers);

                png_destroy_read_struct(&png, &info, NULL);
                fclose(fp);
            }

            RayTracer::Shared::Vec3 PNGSkyBox::sample_color(const RayTracer::Shared::Vec3 &direction) const {
                float theta = acos(-direction.y);
                float phi = atan2(-direction.z, direction.x) + M_PI;

                float u = phi / (2 * M_PI);
                float v = theta / M_PI;

                int x = std::min(static_cast<int>(u * width), width - 1);
                int y = std::min(static_cast<int>(v * height), height - 1);

                png_bytep row = row_pointers[y];
                png_bytep px = &(row[x * 4]);

                return RayTracer::Shared::Vec3(px[0], px[1], px[2]);
                }
            }
        } // namespace Skyboxes
    } // namespace Plugins

