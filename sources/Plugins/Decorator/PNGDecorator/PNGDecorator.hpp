#include <iostream>
#include <vector>
#include <png.h>
#include "IDecorator.hpp"
#include "Material.hpp"
#include "CustomError.hpp"
#include "APrimitive.hpp"
#include "Vec3.hpp"

namespace RayTracer {
    namespace Plugins {
        namespace Decorators {

            class PNGDecorator : public IDecorator {
            public:
                PNGDecorator(const std::string &texturePath);

                void computeColor(RayTracer::Shared::Intersection &intersection,
                                  RayTracer::Shared::Ray const &ray,
                                  RayTracer::Shared::Vec3 &baseColor,
                                  std::unordered_map<RayTracer::Core::EntityType,
                                  std::vector <RayTracer::Core::IEntity * >> entities,
                                  RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) override;
                void orthonormalBasis(const RayTracer::Shared::Vec3 &normal, RayTracer::Shared::Vec3 &tangent, RayTracer::Shared::Vec3 &bitangent);
            private:
                int _width, _height;
                std::vector<std::vector<png_byte>> _rows;

                void loadPNG(const std::string &texturePath);
            };

        } // namespace Decorators
    } // namespace Plugins
} // namespace RayTracer
