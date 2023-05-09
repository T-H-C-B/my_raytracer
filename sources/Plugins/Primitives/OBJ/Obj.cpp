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
            Face face;
            std::string vertex_data;
            while (line_stream >> vertex_data) {
                std::replace(vertex_data.begin(), vertex_data.end(), '/', ' ');
                std::istringstream vertex_stream(vertex_data);
                int vertex_index, uv_index, normal_index;
                vertex_stream >> vertex_index >> uv_index >> normal_index;

                face.v1 = vertex_index - 1;
                face.uv1 = uv_index - 1;
                face.n1 = normal_index - 1;

                line_stream >> vertex_data;
                std::replace(vertex_data.begin(), vertex_data.end(), '/', ' ');
                vertex_stream = std::istringstream(vertex_data);
                vertex_stream >> vertex_index >> uv_index >> normal_index;

                face.v2 = vertex_index - 1;
                face.uv2 = uv_index - 1;
                face.n2 = normal_index - 1;

                line_stream >> vertex_data;
                std::replace(vertex_data.begin(), vertex_data.end(), '/', ' ');
                vertex_stream = std::istringstream(vertex_data);
                vertex_stream >> vertex_index >> uv_index >> normal_index;

                face.v3 = vertex_index - 1;
                face.uv3 = uv_index - 1;
                face.n3 = normal_index - 1;
            }
            _faces.push_back(face);
        }
    }
    file.close();
    std::cout << "Obj file loaded" << std::endl;
    std::cout << "Vertices: " << _vertices.size() << std::endl;
    std::cout << "Normals: " << _normals.size() << std::endl;
    std::cout << "Faces : " << _faces.size() << std::endl;
}

bool RayTracer::Plugins::Primitives::Obj::rayTriangleIntersection(const RayTracer::Shared::Ray& ray, const Face& face, float& t) const
{
    const float EPSILON = 1e-6f;
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

