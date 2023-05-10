/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Torus
*/

#include <cmath>
#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <numeric>
#include "Torus.hpp"

RayTracer::Plugins::Primitives::Torus::Torus(const RayTracer::Shared::Vec3& position, float majorRadius, float minorRadius, const RayTracer::Shared::Vec3& rotation)
: APrimitive(position, rotation), _majorRadius(majorRadius), _minorRadius(minorRadius), _rotation(rotation)
{
    std::cout << "Torus created" << std::endl;
}

void RayTracer::Plugins::Primitives::Torus::scale(float scale) {
    _majorRadius *= scale;
    _minorRadius *= scale;
}

int RayTracer::Plugins::Primitives::Torus::solveQuadratic(double coefficients[3], double roots[2]) const {
    double a = coefficients[0];
    double b = coefficients[1];
    double c = coefficients[2];

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0;
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    roots[0] = (-b - sqrtDiscriminant) / (2 * a);
    roots[1] = (-b + sqrtDiscriminant) / (2 * a);

    return 2;
}

int RayTracer::Plugins::Primitives::Torus::solveCubic(double coefficients[4], double roots[3]) const {
    double a = coefficients[0];
    double b = coefficients[1];
    double c = coefficients[2];
    double d = coefficients[3];

    double f = ((3 * c / a) - ((b * b) / (a * a))) / 3;
    double g = ((2 * (b * b * b) / (a * a * a)) - (9 * b * c / (a * a)) + (27 * d / a)) / 27;
    double h = (g * g / 4) + (f * f * f / 27);

    if (h > 0) {
        double r = -(g / 2) + std::sqrt(h);
        double sgn_r = (r < 0) ? -1 : 1;
        double s = sgn_r * std::pow(sgn_r * r, 1.0 / 3);

        double t = -(g / 2) - std::sqrt(h);
        double sgn_t = (t < 0) ? -1 : 1;
        double u = sgn_t * std::pow(sgn_t * t, 1.0 / 3);

        roots[0] = s + u - (b / (3 * a));
        return 1;
    }

    if (h == 0 && f == 0 && g == 0) {
        double sgn_d = (d < 0) ? -1 : 1;
        roots[0] = -sgn_d * std::pow(sgn_d * d, 1.0 / 3);
        return 1;
    }

    double i = std::sqrt(((g * g) / 4) - h);
    double j = std::pow(i, 1.0 / 3);
        double k = std::acos(-(g / (2 * i)));
    double l = -j;
    double m = std::cos(k / 3);
    double n = std::sqrt(3) * std::sin(k / 3);
    double p = -(b / (3 * a));

    roots[0] = 2 * l * m + p;
    roots[1] = l * (m + n) + p;
    roots[2] = l * (m - n) + p;

    return 3;
}

double RayTracer::Plugins::Primitives::Torus::solveQuartic(double coefficients[5], double roots[4]) const {
    double a = coefficients[0];
    double b = coefficients[1];
    double c = coefficients[2];
    double d = coefficients[3];
    double e = coefficients[4];

    double cubic_coefficients[4] = {a,
                                     -4 * e,
                                     2 * c * c - 4 * b * d,
                                     -8 * c * e + 4 * b * e * e};

    double cubic_roots[3];
    int num_cubic_roots = solveCubic(cubic_coefficients, cubic_roots);

    double y = cubic_roots[0];
    double R = b * b - 4 * a * c + 4 * b * y - 8 * d;

    double D, E;
    if (R < 0) {
        double sqrtR = std::sqrt(-R);
        D = 0.5 * sqrtR;
        E = -0.5 * sqrtR;
    } else {
        double sqrtR = std::sqrt(R);
        D = 0.5 * sqrtR;
        E = -0.5 * sqrtR;
    }

    double quadratic_coefficients1[3] = {a,
                                         b + y - D,
                                         c - e};

    double quadratic_coefficients2[3] = {a,
                                         b + y + D,
                                         c - e};

    double quadratic_roots1[2];
    double quadratic_roots2[2];
    int num_roots1 = solveQuadratic(quadratic_coefficients1, quadratic_roots1);
    int num_roots2 = solveQuadratic(quadratic_coefficients2, quadratic_roots2);

    for (int i = 0; i < num_roots1; i++) {
        roots[i] = quadratic_roots1[i];
    }

    for (int i = 0; i < num_roots2; i++) {
        roots[num_roots1 + i] = quadratic_roots2[i];
    }

    return num_roots1 + num_roots2;
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> RayTracer::Plugins::Primitives::Torus::intersect(const RayTracer::Shared::Ray &ray, float &t) const {
    double dx = ray.getDirection().x;
    double dy = ray.getDirection().y;
    double dz = ray.getDirection().z;
    double ox = ray.getOrigin().x - _position.x;
    double oy = ray.getOrigin().y - _position.y;
    double oz = ray.getOrigin().z - _position.z;

    double coefficients[5];
    coefficients[0] = dx * dx + dy * dy + dz * dz;
    coefficients[1] = 4 * (dx * ox + dy * oy + dz *     oz);
    coefficients[2] = 2 * (_majorRadius * _majorRadius + 2 * (ox * ox + oy * oy + oz * oz) - _minorRadius * _minorRadius);
    coefficients[3] = 4 * (ox * ox + oy * oy + oz * oz - _majorRadius * _majorRadius);
    coefficients[4] = ox * ox + oy * oy + oz * oz - _majorRadius * _majorRadius;

    double roots[4];
    int numRoots = solveQuartic(coefficients, roots);

    bool hasIntersection = false;
    float minT = std::numeric_limits<float>::max();

    for (int i = 0; i < numRoots; i++) {
        if (roots[i] > 0 && roots[i] < minT) {
            minT = roots[i];
            hasIntersection = true;
        }
    } 

    if (hasIntersection) {
        t = minT;
        auto intersection = std::make_unique<RayTracer::Shared::Intersection>();
        intersection->point = ray.getOrigin() + ray.getDirection() * t;

        RayTracer::Shared::Vec3 normal = (intersection->point - _position);
        normal.z = 0;
        normal.normalize();

        float dist = (intersection->point - _position).length() - _majorRadius;
        intersection->normal = (intersection->point - _position - normal * dist).normalize();

        return intersection;
    } else {
        return std::nullopt;
    }
}


   


