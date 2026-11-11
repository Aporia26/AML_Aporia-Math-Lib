#pragma once
#include "Geometry.hpp"
#include <algorithm>

namespace AML
{
    // Circle vs. Circle
    inline bool overlap_circle(const circle& a, const circle& b)
    {
        float dist_sqr = length_sqr(b.center - a.center);
        float r_sum = a.radius + b.radius;
        return dist_sqr <= (r_sum * r_sum);
    }

    // Rectangle vs. Rectangle
    inline bool overlap_aabb2d(const AABB2D& a, const AABB2D& b)
    {
        return (a.max_pt.x >= b.min_pt.x && a.min_pt.x <= b.max_pt.x) &&
               (a.max_pt.y >= b.min_pt.y && a.min_pt.y <= b.max_pt.y);
    }

    // Circle vs. AABB2D 
    inline bool overlap_circle_vs_aabb(const circle& c, const AABB2D& box)
    {
        float closest_x = std::max(box.min_pt.x, std::min(c.center.x, box.max_pt.x));
        float closest_y = std::max(box.min_pt.y, std::min(c.center.y, box.max_pt.y));

        vec2 closest_point(closest_x, closest_y);
        float dist_sqr = length_sqr(closest_point - c.center);
        
        return dist_sqr <= (c.radius * c.radius);
    }
    //SAT
    inline bool overlap_obb2d(const OBB2D& a, const OBB2D& b)
    {
        // 2D Rotation transformation to find local coordinate vectors
        vec2 ax(std::cos(a.angleRadians), std::sin(a.angleRadians));
        vec2 ay(-std::sin(a.angleRadians), std::cos(a.angleRadians));
        vec2 bx(std::cos(b.angleRadians), std::sin(b.angleRadians));
        vec2 by(-std::sin(b.angleRadians), std::cos(b.angleRadians));

        vec2 T = b.center - a.center;

        // Test the 4 potential separating axes (2 from Box A, 2 from Box B)
        vec2 axes[4] = { ax, ay, bx, by };

        for (int i = 0; i < 4; ++i)
        {
            vec2 L = axes[i];

            // Project half-widths onto target axis
            float rA = a.extents.x * std::abs(dot(ax, L)) + a.extents.y * std::abs(dot(ay, L));
            float rB = b.extents.x * std::abs(dot(bx, L)) + b.extents.y * std::abs(dot(by, L));

            // If absolute center distance exceeds combined projection radius, space is clear
            if (std::abs(dot(T, L)) > rA + rB)
            {
                return false; // Found a separating plane axis -> No collision
            }
        }
        return true; // Check 4 directions -> found no tracking gap -> Collision detected
    }

    //3d
    inline bool sphere_vs_sphere(const vec3& centerA, float radiusA, const vec3& centerB, float radiusB) 
    {
     //squared distance avoiding std::sqrt() 
     float distanceSqr = length_sqr(centerB - centerA);
     float radiusSum = radiusA + radiusB;
     return distanceSqr <= (radiusSum * radiusSum);
    }

    // 3D AABB vs AABB 
    inline bool overlap_aabb(const AABB& a, const AABB& b)
    {
        return (a.max_pt.x >= b.min_pt.x && a.min_pt.x <= b.max_pt.x) &&
               (a.max_pt.y >= b.min_pt.y && a.min_pt.y <= b.max_pt.y) &&
               (a.max_pt.z >= b.min_pt.z && a.min_pt.z <= b.max_pt.z);
    }

    // Ray vs 3D AABB 
    inline bool hit_aabb(const ray& r, const AABB& box, float t_min, float t_max, float& hit_t)
    {
        for (int axis = 0; axis < 3; ++axis)
        {
            float origin = (axis == 0) ? r.origin.x : (axis == 1 ? r.origin.y : r.origin.z);
            float dir    = (axis == 0) ? r.direction.x : (axis == 1 ? r.direction.y : r.direction.z);
            float bmin   = (axis == 0) ? box.min_pt.x : (axis == 1 ? box.min_pt.y : box.min_pt.z);
            float bmax   = (axis == 0) ? box.max_pt.x : (axis == 1 ? box.max_pt.y : box.max_pt.z);

            float invD = (std::abs(dir) < 1e-8f) ? ((dir < 0.0f) ? -1e8f : 1e8f) : (1.0f / dir);
            float t0 = (bmin - origin) * invD;
            float t1 = (bmax - origin) * invD;
            if (invD < 0.0f) std::swap(t0, t1);

            t_min = std::max(t0, t_min);
            t_max = std::min(t1, t_max);
            if (t_max <= t_min) return false;
        }
        hit_t = t_min;
        return true;
    }

}