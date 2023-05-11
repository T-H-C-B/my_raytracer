/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder
*/

#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include "Ray.hpp"
#include "Obj.hpp"
#include "ConfigError.hpp"

RayTracer::Plugins::Primitives::Obj::Obj(const RayTracer::Shared::Vec3& position, const RayTracer::Shared::Vec3& rotation, const std::string &path, float Ascale)
: APrimitive(position, rotation), _scale(Ascale)
{
    try {
        loadObjFile(path);
        scale(_scale);
        rotate(rotation);
        std::cout << "Obj created" << std::endl;
    } catch (const RayTracer::Shared::ConfigError& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        throw;
    }
}

void RayTracer::Plugins::Primitives::Obj::scale(float scale) {
    for (auto& vertex : _vertices) {
        vertex *= scale;
    }
}

void RayTracer::Plugins::Primitives::Obj::rotate(const RayTracer::Shared::Vec3& rotation)
{
    float cos_x = std::cos(rotation.x * M_PI / 180.0);
    float sin_x = std::sin(rotation.x * M_PI / 180.0);
    float cos_y = std::cos(rotation.y * M_PI / 180.0);
    float sin_y = std::sin(rotation.y * M_PI / 180.0);
    float cos_z = std::cos(rotation.z * M_PI / 180.0);
    float sin_z = std::sin(rotation.z * M_PI / 180.0);

    for (auto& vertex : _vertices) {
        float new_y = vertex.y * cos_x - vertex.z * sin_x;
        float new_z = vertex.y * sin_x + vertex.z * cos_x;
        vertex.y = new_y;
        vertex.z = new_z;

        float new_x = vertex.x * cos_y + vertex.z * sin_y;
        new_z = -vertex.x * sin_y + vertex.z * cos_y;
        vertex.x = new_x;
        vertex.z = new_z;

        new_x = vertex.x * cos_z - vertex.y * sin_z;
        new_y = vertex.x * sin_z + vertex.y * cos_z;
        vertex.x = new_x;
        vertex.y = new_y;
    }
}

void RayTracer::Plugins::Primitives::Obj::loadObjFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw RayTracer::Shared::ConfigError("Obj", "Cannot open file " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        std::string prefix;
        line_stream >> prefix;

        if (prefix == "v") {
            RayTracer::Shared::Vec3 vertex;
            line_stream >> vertex.x >> vertex.y >> vertex.z;
            vertex += _position;
            _vertices.push_back(vertex);
        } else if (prefix == "vn") {
            RayTracer::Shared::Vec3 normal;
            line_stream >> normal.x >> normal.y >> normal.z;
            _normals.push_back(normal);
        } else if (prefix == "vt") {
            RayTracer::Shared::Vec2 uv;
            line_stream >> uv.x >> uv.y;
            _uvs.push_back(uv);
        } else if (prefix == "f") {
            std::vector<int> vertex_indices, uv_indices, normal_indices;

            std::string vertex_data;
            while (line_stream >> vertex_data) {
                std::replace(vertex_data.begin(), vertex_data.end(), '/', ' ');
                std::istringstream vertex_stream(vertex_data);
                int vertex_index, uv_index, normal_index;
                vertex_stream >> vertex_index;

                if (!vertex_stream.eof()) {
                    vertex_stream.ignore();
                    if (vertex_stream.peek() != '/') {
                        vertex_stream >> uv_index;
                    }
                }

                if (!vertex_stream.eof()) {
                    vertex_stream.ignore();
                    vertex_stream >> normal_index;
                }

                vertex_indices.push_back(vertex_index - 1);
                uv_indices.push_back(uv_index - 1);
                normal_indices.push_back(normal_index - 1);
            }

            for (size_t i = 1; i < vertex_indices.size() - 1; ++i) {
                Face face;
                face.v1 = vertex_indices[0];
                face.uv1 = uv_indices[0];
                face.n1 = normal_indices[0];

                face.v2 = vertex_indices[i];
                face.uv2 = uv_indices[i];
                face.n2 = normal_indices[i];

                face.v3 = vertex_indices[i + 1];
                face.uv3 = uv_indices[i + 1];
                face.n3 = normal_indices[i + 1];

                _faces.push_back(face);
            }
        }
    }
    file.close();
}

bool RayTracer::Plugins::Primitives::Obj::rayTriangleIntersection(const RayTracer::Shared::Ray& ray, const Face& face, float& t) const
{
    const float EPSILON = 1e-4f;
    RayTracer::Shared::Vec3 v1 = _vertices[face.v1];
    RayTracer::Shared::Vec3 v2 = _vertices[face.v2];
    RayTracer::Shared::Vec3 v3 = _vertices[face.v3];

    RayTracer::Shared::Vec3 edge1 = v2 - v1;
    RayTracer::Shared::Vec3 edge2 = v3 - v1;
    RayTracer::Shared::Vec3 h = ray.getDirection().cross(edge2);
    float a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    float f = 1.0f / a;
    RayTracer::Shared::Vec3 s = ray.getOrigin() - v1;
    float u = f * s.dot(h);

    if (u < 0.0f || u > 1.0f)
        return false;

    RayTracer::Shared::Vec3 q = s.cross(edge1);
    float v = f * ray.getDirection().dot(q);

    if (v < 0.0f || u + v > 1.0f)
        return false;

    t = f * edge2.dot(q);

    if (t > EPSILON)
        return true;
    else
        return false;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Obj::intersect(const RayTracer::Shared::Ray& ray, float& t) const
{
    float closest_t = t;
    RayTracer::Shared::Intersection closest_intersection;

    for (const auto& face : _faces) {
        RayTracer::Shared::Vec3 v0 = _vertices[face.v1];
        RayTracer::Shared::Vec3 v1 = _vertices[face.v2];
        RayTracer::Shared::Vec3 v2 = _vertices[face.v3];
        float current_t = t;

        if (rayTriangleIntersection(ray, face, current_t) && current_t < closest_t) {
            closest_t = current_t;
            closest_intersection.hit = true;
            closest_intersection.t = current_t;
            closest_intersection.point = ray.pointAt(current_t);
            closest_intersection.normal = (v1 - v0).cross(v2 - v0);
        }
    }
    if (closest_intersection.hit) {
        auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
        intersection->hit = true;
        intersection->t = closest_intersection.t;
        t = closest_intersection.t;
        intersection->point = closest_intersection.point;
        intersection->normal = closest_intersection.normal;
        intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;
        return intersection;
    } else {
        return std::nullopt;
    }
}

