#pragma once
#include "Vector.hpp"

namespace AML
{
    struct circle
    {
        vec2 center;
        float radius;

        constexpr circle() : center(0.0f, 0.0f), radius(1.0f) {}
        constexpr circle(const vec2& c, float r) : center(c), radius(r) {}
    };

    struct AABB2D //no rotatn
    {
        vec2 min_pt;
        vec2 max_pt;

        constexpr AABB2D() : min_pt(0.0f, 0.0f), max_pt(0.0f, 0.0f) {}
        constexpr AABB2D(const vec2& min, const vec2& max) : min_pt(min), max_pt(max) {}
    };

    struct OBB2D  //rotatn
    {
        vec2 center;
        vec2 extents;      //(half-width, half-height)
        float angleRadians; 

        constexpr OBB2D() : center(0.0f, 0.0f), extents(0.5f, 0.5f), angleRadians(0.0f) {}
        constexpr OBB2D(const vec2& c, const vec2& e, float a) : center(c), extents(e), angleRadians(a) {}
    };

    struct plane
    {
        vec3 normal;
        float distance;

        constexpr plane() : normal(0.0f, 1.0f, 0.0f), distance(0.0f) {}
        constexpr plane(const vec3& n, float d) : normal(normalize(n)), distance(d) {}

        //Returns > 0 if point is in front, < 0 if behind plane
        inline float distance_to_point(const vec3& pt) const
        {
            return dot(normal, pt) + distance;
        }
    };

    struct sphere
    {
        vec3 centre;
        float radius;

        constexpr sphere() : centre(0.0f, 0.0f, 0.0f), radius(1.0f) {}
        constexpr sphere(const vec3& c, float r) : centre(c), radius(r) {}

        // Ray-Sphere Intersection 
        inline bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
        {
            vec3 oc = r.origin - centre;
            
            //at^2 + bt + c = 0
            float a = length_sqr(r.direction); // Equal to 1.0f if ray.dir is normalized
            float half_b = dot(oc, r.direction);
            float c = length_sqr(oc) - radius * radius;

            //half-b optimization 
            float discriminant = half_b * half_b - a * c;
            if (discriminant < 0.0f) 
            {
                return false; // Discriminant is negative -> Ray missed the sphere 
            }
            
            float sqrtd = std::sqrt(discriminant);

            // Find the nearest root equation intersection point within acceptable t constraints
            float root = (-half_b - sqrtd) / a;
            if (root < t_min || t_max < root) 
            {
                root = (-half_b + sqrtd) / a; // Try the second farther root equation slice
                if (root < t_min || t_max < root)
                {
                    return false; // Neither intersection falls inside our clipping bounds
                }
            }

            //record collision diagnostics
            rec.t = root;
            rec.point = r.at(rec.t);
            vec3 outward_normal = (rec.point - centre) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }
    };
}