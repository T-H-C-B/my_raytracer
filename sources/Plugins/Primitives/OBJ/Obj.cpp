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
    float closest_intersection = std::numeric_limits<float>::max();
    bool intersection_found = false;

    RayTracer::Shared::Intersection closest_intersection_data;

    for (const auto& face : _faces) {
        RayTracer::Shared::Vec3 v0 = _vertices[face.v1];
        RayTracer::Shared::Vec3 v1 = _vertices[face.v2];
        RayTracer::Shared::Vec3 v2 = _vertices[face.v3];
        float current_t;

        if (rayTriangleIntersection(ray, face, current_t) && current_t < closest_intersection) {
            intersection_found = true;
            closest_intersection = current_t;

            RayTracer::Shared::Vec3 intersection_point = ray.pointAt(current_t);
            RayTracer::Shared::Vec3 normal_v1 = _normals[face.n1];
            RayTracer::Shared::Vec3 normal_v2 = _normals[face.n2];
            RayTracer::Shared::Vec3 normal_v3 = _normals[face.n3];

            RayTracer::Shared::Vec3 v0v2 = v2 - v0;
            RayTracer::Shared::Vec3 v0v1 = v1 - v0;
            RayTracer::Shared::Vec3 v1v2 = v2 - v1;
            RayTracer::Shared::Vec3 pvec = ray.getDirection().cross(v1v2);
            float det = v0v1.dot(pvec);

            RayTracer::Shared::Vec3 tvec = intersection_point - v0;
            float u = tvec.dot(pvec) / det;
            RayTracer::Shared::Vec3 qvec = tvec.cross(v0v1);
            float v = ray.getDirection().dot(qvec) / det;
            float w = 1.0f - u - v;

            RayTracer::Shared::Vec3 normal = RayTracer::Shared::Vec3(u * normal_v1.x + v * normal_v2.x + w * normal_v3.x,
                                                                     u * normal_v1.y + v * normal_v2.y + w * normal_v3.y,
                                                                     u * normal_v1.z + v * normal_v2.z + w * normal_v3.z).normalize();

            closest_intersection_data.hit = true;
            closest_intersection_data.t = current_t;
            closest_intersection_data.point = intersection_point;
            closest_intersection_data.normal = normal;
        }
    }
    if (intersection_found) {
        printf("Intersection found\n");
        auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
        *intersection = closest_intersection_data;
        intersection->primitive = (RayTracer::Plugins::Primitives::APrimitive *)this;
        t = closest_intersection;
        return intersection;
    } else {
        return std::nullopt;
    }
}
