#pragma once
#include "Geometry.hpp"

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
}