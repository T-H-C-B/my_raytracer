#include "PNGDecorator.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {

            PNGDecorator::PNGDecorator(const std::string &texturePath) {
                loadPNG(texturePath);
            }

            void PNGDecorator::computeColor(RayTracer::Shared::Intersection &intersection,
                                            RayTracer::Shared::Ray const &ray,
                                            RayTracer::Shared::Vec3 &baseColor,
                                            std::unordered_map<RayTracer::Core::EntityType,
                                            std::vector <RayTracer::Core::IEntity * >> entities,
                                            RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
                float u = intersection.point.x - floor(intersection.point.x);
                float v = intersection.point.z - floor(intersection.point.z);

                int x = static_cast<int>(u * (_width - 1));
                int y = static_cast<int>(v * (_height - 1));

                const auto &row = _rows[y];
                float r = static_cast<float>(row[x * 3]) / 255.0f;
                float g = static_cast<float>(row[x * 3 + 1]) / 255.0f;
                float b = static_cast<float>(row[x * 3 + 2]) / 255.0f;

                RayTracer::Shared::Vec3 textureColor(r, g, b);

                baseColor.x = baseColor.x * textureColor.x;
                baseColor.y = baseColor.y * textureColor.y;
                baseColor.z = baseColor.z * textureColor.z;
            }


            void PNGDecorator::loadPNG(const std::string &texturePath) {
                FILE *file = fopen(texturePath.c_str(), "rb");
                if (!file) {
                    throw Shared::CustomError("PNGDecorator: Unable to open texture file");
                }

                png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
                if (!png) {
                    fclose(file);
                    throw Shared::CustomError("PNGDecorator: Error initializing libpng read struct");
                }

                png_infop info = png_create_info_struct(png);
                if (!info) {
                    fclose(file);
                    png_destroy_read_struct(&png, NULL, NULL);
                    throw Shared::CustomError("PNGDecorator: Error initializing libpng info struct");
                }

                if (setjmp(png_jmpbuf(png))) {
                    fclose(file);
                    png_destroy_read_struct(&png, &info, NULL);
                    throw Shared::CustomError("PNGDecorator: Error reading PNG file");
                }

                png_init_io(png, file);
                png_read_info(png, info);

                _width = png_get_image_width(png, info);
                _height = png_get_image_height(png, info);
                png_byte colorType = png_get_color_type(png, info);
                png_byte bitDepth = png_get_bit_depth(png, info);

                if (bitDepth == 16) {
                    png_set_strip_16(png);
                }

                if (colorType == PNG_COLOR_TYPE_PALETTE) {
                    png_set_palette_to_rgb(png);
                }

                if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
                    png_set_expand_gray_1_2_4_to_8(png);
                }

                if (png_get_valid(png, info, PNG_INFO_tRNS)) {
                    png_set_tRNS_to_alpha(png);
                }

                if (colorType == PNG_COLOR_TYPE_RGB ||
                    colorType == PNG_COLOR_TYPE_GRAY ||
                    colorType == PNG_COLOR_TYPE_PALETTE) {
                    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
                }

                if (colorType == PNG_COLOR_TYPE_GRAY ||
                    colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
                    png_set_gray_to_rgb(png);
                }

                png_read_update_info(png, info);

                _rows.resize(_height);
                for (int y = 0; y < _height; y++) {
                    _rows[y].resize(png_get_rowbytes(png, info));
                }

                for (int y = 0; y < _height; y++) {
                    png_read_row(png, _rows[y].data(), NULL);
                }

                png_read_end(png, NULL);
                fclose(file);
                png_destroy_read_struct(&png, &info, NULL);
            }

        } // namespace Decorators
    } // namespace Plugins
} // namespace RayTracer
