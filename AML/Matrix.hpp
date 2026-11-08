#pragma once
#include"Vector.hpp"

namespace AML
{
    struct mat3
    {
        union      //column major
        {
        vec3 col[3];
        float data[9];
        };

        mat3() : col{            //default identity
            vec3(1.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f),
            vec3(0.0f, 0.0f, 1.0f)
        } {}
        //or with col
        mat3(const vec3& c0, const vec3& c1, const vec3& c2) 
            : col{ c0, c1, c2 } {}

        inline vec3& operator[](int index) { return col[index]; }
        inline const vec3& operator[](int index) const { return col[index]; }
    };

    //basic operations
    inline mat3 operator+(const mat3& lhs, const mat3& rhs)
    {
        return mat3(
            lhs.col[0] + rhs.col[0],
            lhs.col[1] + rhs.col[1],
            lhs.col[2] + rhs.col[2]
        );
    }
    inline mat3 operator-(const mat3& lhs, const mat3& rhs)
    {
        return mat3(
            lhs.col[0] - rhs.col[0],
            lhs.col[1] - rhs.col[1],
            lhs.col[2] - rhs.col[2]
        );
    }
    inline mat3 operator*(const mat3& lhs, float scalar)
    {
        return mat3(
            lhs.col[0] * scalar,
            lhs.col[1] * scalar,
            lhs.col[2] * scalar
        );
    }    
     inline mat3 operator*(float scalar, const mat3& lhs)
    {
        return mat3(
            lhs.col[0] * scalar,
            lhs.col[1] * scalar,
            lhs.col[2] * scalar
        );
    } 
    inline mat3 operator*(float scalar, const mat3& rhs)
    {
        return rhs * scalar;
    }

    //matrix utils
    inline vec3 operator*(const mat3& lhs, const vec3& rhs)  //transform 3d or 2d (mat x vec)
    {
        return vec3(
            lhs.col[0].x * rhs.x + lhs.col[1].x * rhs.y + lhs.col[2].x * rhs.z,
            lhs.col[0].y * rhs.x + lhs.col[1].y * rhs.y + lhs.col[2].y * rhs.z,
            lhs.col[0].z * rhs.x + lhs.col[1].z * rhs.y + lhs.col[2].z * rhs.z
        );
    }
    inline mat3 operator*(const mat3& lhs, const mat3& rhs)
    {
        mat3 result;

        // Column-Major matrix multiplication loop
        for (int i = 0; i < 3; ++i)
            {
            result[i].x = lhs.col[0].x * rhs[i].x + lhs.col[1].x * rhs[i].y + lhs.col[2].x * rhs[i].z;
            result[i].y = lhs.col[0].y * rhs[i].x + lhs.col[1].y * rhs[i].y + lhs.col[2].y * rhs[i].z;
            result[i].z = lhs.col[0].z * rhs[i].x + lhs.col[1].z * rhs[i].y + lhs.col[2].z * rhs[i].z;
            }

        return result;
    }
    inline float det(const mat3& m)
    {
        // The triple scalar product: det(M) = col0 . (col1 x col2)
        return dot(m.col[0], cross(m.col[1], m.col[2]));
    }
    inline mat3 inverse(const mat3& m)
    {
        float detr = det(m);
        
        // determinant 0 means the matrix cannot be inverted (flattened space)
        if (std::abs(detr) < 1e-6f)
        {
            return mat3(); 
        }

        float invDet = 1.0f / detr;

        // Compute the adjugate 
        vec3 c0 = cross(m.col[1], m.col[2]);
        vec3 c1 = cross(m.col[2], m.col[0]);
        vec3 c2 = cross(m.col[0], m.col[1]);

        // Transpose and scale 
        return mat3(
            vec3(c0.x * invDet, c1.x * invDet, c2.x * invDet),
            vec3(c0.y * invDet, c1.y * invDet, c2.y * invDet),
            vec3(c0.z * invDet, c1.z * invDet, c2.z * invDet)
        );
    }
    inline std::ostream& operator<<(std::ostream& os, const mat3& m)
    {
        os << "\n| " << m.col[0].x << "\t" << m.col[1].x << "\t" << m.col[2].x << " |\n"
           << "| " << m.col[0].y << "\t" << m.col[1].y << "\t" << m.col[2].y << " |\n"
           << "| " << m.col[0].z << "\t" << m.col[1].z << "\t" << m.col[2].z << " |";
        return os;
    }
    inline mat3 transpose(const mat3& m)
    {
        return mat3(
            vec3(m.col[0].x, m.col[1].x, m.col[2].x),
            vec3(m.col[0].y, m.col[1].y, m.col[2].y),
            vec3(m.col[0].z, m.col[1].z, m.col[2].z)
        );
    }


    struct mat4
    {
        union {
            vec4 col[4];       
            float data[16];    
        };

        constexpr mat4() 
        : col{
            vec4(1.0f, 0.0f, 0.0f, 0.0f),
            vec4(0.0f, 1.0f, 0.0f, 0.0f),
            vec4(0.0f, 0.0f, 1.0f, 0.0f),
            vec4(0.0f, 0.0f, 0.0f, 1.0f)
        } {}

        // Custom Constructor: Initialize with 4 explicit column vectors
        constexpr mat4(const vec4& c0, const vec4& c1, const vec4& c2, const vec4& c3) 
            : col{ c0, c1, c2, c3 } {}

        // operators to fetch column vectors (e.g., myMatrix[0])
        inline vec4& operator[](int index) { return col[index]; }
        inline const vec4& operator[](int index) const { return col[index]; }
    };

    //basic operations
    inline mat4 operator+(const mat4& lhs, const mat4& rhs)
    {
        return mat4(
            lhs.col[0] + rhs.col[0],
            lhs.col[1] + rhs.col[1],
            lhs.col[2] + rhs.col[2],
            lhs.col[3] + rhs.col[3]
        );
    }

    inline mat4 operator-(const mat4& lhs, const mat4& rhs)
    {
        return mat4(
            lhs.col[0] - rhs.col[0],
            lhs.col[1] - rhs.col[1],
            lhs.col[2] - rhs.col[2],
            lhs.col[3] - rhs.col[3]
        );
    }

    inline mat4 operator*(const mat4& lhs, float scalar)
    {
        return mat4(
            lhs.col[0] * scalar,
            lhs.col[1] * scalar,
            lhs.col[2] * scalar,
            lhs.col[3] * scalar
        );
    }
    inline mat4 operator*(float scalar, const mat4& rhs)
    {
        return rhs * scalar;
    }

//matrix utils
    inline vec4 operator*(const mat4& lhs, const vec4& rhs) // Mat × Vec
    {
        return vec4(
            lhs.col[0].x * rhs.x + lhs.col[1].x * rhs.y + lhs.col[2].x * rhs.z + lhs.col[3].x * rhs.w,
            lhs.col[0].y * rhs.x + lhs.col[1].y * rhs.y + lhs.col[2].y * rhs.z + lhs.col[3].y * rhs.w,
            lhs.col[0].z * rhs.x + lhs.col[1].z * rhs.y + lhs.col[2].z * rhs.z + lhs.col[3].z * rhs.w,
            lhs.col[0].w * rhs.x + lhs.col[1].w * rhs.y + lhs.col[2].w * rhs.z + lhs.col[3].w * rhs.w
        );
    }

    inline mat4 operator*(const mat4& lhs, const mat4& rhs) // (mat4 * mat4)
    {
        mat4 result;
        for (int i = 0; i < 4; ++i)
        {
            result[i].x = lhs.col[0].x * rhs[i].x + lhs.col[1].x * rhs[i].y + lhs.col[2].x * rhs[i].z + lhs.col[3].x * rhs[i].w;
            result[i].y = lhs.col[0].y * rhs[i].x + lhs.col[1].y * rhs[i].y + lhs.col[2].y * rhs[i].z + lhs.col[3].y * rhs[i].w;
            result[i].z = lhs.col[0].z * rhs[i].x + lhs.col[1].z * rhs[i].y + lhs.col[2].z * rhs[i].z + lhs.col[3].z * rhs[i].w;
            result[i].w = lhs.col[0].w * rhs[i].x + lhs.col[1].w * rhs[i].y + lhs.col[2].w * rhs[i].z + lhs.col[3].w * rhs[i].w;
        }
        return result;
    }
    
    inline mat4 transpose(const mat4& m)
    {
        return mat4(
            vec4(m.col[0].x, m.col[1].x, m.col[2].x, m.col[3].x),
            vec4(m.col[0].y, m.col[1].y, m.col[2].y, m.col[3].y),
            vec4(m.col[0].z, m.col[1].z, m.col[2].z, m.col[3].z),
            vec4(m.col[0].w, m.col[1].w, m.col[2].w, m.col[3].w)
        );
    }

    inline std::ostream& operator<<(std::ostream& os, const mat4& m)
    {
        os << "\n| " << m.col[0].x << "\t" << m.col[1].x << "\t" << m.col[2].x << "\t" << m.col[3].x << " |\n"
           << "| " << m.col[0].y << "\t" << m.col[1].y << "\t" << m.col[2].y << "\t" << m.col[3].y << " |\n"
           << "| " << m.col[0].z << "\t" << m.col[1].z << "\t" << m.col[2].z << "\t" << m.col[3].z << " |\n"
           << "| " << m.col[0].w << "\t" << m.col[1].w << "\t" << m.col[2].w << "\t" << m.col[3].w << " |";
        return os;
    }

    //Transformations
    inline mat4 translate(float tx, float ty, float tz)
    {
        mat4 result; 
        // Fourth column holds the translation offsets multiplied by the w component (1.0)
        result[3] = vec4(tx, ty, tz, 1.0f);
        return result;
    }

    inline mat4 translate(const vec3& translation)
    {
        return translate(translation.x, translation.y, translation.z);
    }

    inline mat4 scale(float sx, float sy, float sz)
    {
        mat4 result;
        result[0].x = sx; // Scale X
        result[1].y = sy; // Scale Y
        result[2].z = sz; // Scale Z
        return result;
    }

    inline mat4 scale(const vec3& scaleFactors)
    {
        return scale(scaleFactors.x, scaleFactors.y, scaleFactors.z);
    }

    // Rotate around the X-Axis (Pitch)
    inline mat4 rotateX(float angleRadians)
    {
        mat4 result;
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        result[1] = vec4(0.0f,  c, s, 0.0f);
        result[2] = vec4(0.0f, -s, c, 0.0f);
        return result;
    }

    // Rotate around the Y-Axis (Yaw)
    inline mat4 rotateY(float angleRadians)
    {
        mat4 result;
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        result[0] = vec4(c, 0.0f, -s, 0.0f);
        result[2] = vec4(s, 0.0f,  c, 0.0f);
        return result;
    }

    // Rotate around the Z-Axis (Roll)
    inline mat4 rotateZ(float angleRadians)
    {
        mat4 result;
        float c = std::cos(angleRadians);
        float s = std::sin(angleRadians);

        result[0] = vec4( c, s, 0.0f, 0.0f);
        result[1] = vec4(-s, c, 0.0f, 0.0f);
        return result;
    }

    //Camera Matrices
    inline mat4 look_at(const vec3& eye, const vec3& target, const vec3& up)
    {
        // camera's local coordinate axes
        vec3 zaxis = normalize(eye - target);    // Forward direction vector (pointing backwards)
        vec3 xaxis = normalize(cross(up, zaxis)); // Right direction vector
        vec3 yaxis = cross(zaxis, xaxis);         // Up direction vector

        mat4 orientation(
            vec4(xaxis.x, yaxis.x, zaxis.x, 0.0f),
            vec4(xaxis.y, yaxis.y, zaxis.y, 0.0f),
            vec4(xaxis.z, yaxis.z, zaxis.z, 0.0f),
            vec4(0.0f,    0.0f,    0.0f,    1.0f)
        );

        mat4 translation = translate(eye * -1.0f);

        //combo orientation and translation to get final view space grid
        return orientation * translation;
    }

    inline mat4 perspective(float fovyRadians, float aspect, float zNear, float zFar)
    {
        mat4 result; // Default constructor zeros out data except for 1s
        float tanHalfFovy = std::tan(fovyRadians / 2.0f);

        // dont wanna use identity here as initial
        result[0] = vec4(0.0f, 0.0f, 0.0f, 0.0f);
        result[1] = vec4(0.0f, 0.0f, 0.0f, 0.0f);
        result[2] = vec4(0.0f, 0.0f, 0.0f, 0.0f);
        result[3] = vec4(0.0f, 0.0f, 0.0f, 0.0f);

        // putting Column-Major perspective projection constraints
        result[0].x = 1.0f / (aspect * tanHalfFovy);
        result[1].y = 1.0f / (tanHalfFovy);
        result[2].z = -(zFar + zNear) / (zFar - zNear);
        result[2].w = -1.0f;                               // Stores depth inside the w for perspective
        result[3].z = -(2.0f * zFar * zNear) / (zFar - zNear);

        return result;
    }

    inline mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        mat4 result;

        result[0].x = 2.0f / (right - left);
        result[1].y = 2.0f / (top - bottom);
        result[2].z = -2.0f / (zFar - zNear);

        result[3].x = -(right + left) / (right - left);
        result[3].y = -(top + bottom) / (top - bottom);
        result[3].z = -(zFar + zNear) / (zFar - zNear);
        result[3].w = 1.0f;

        return result;
    }

}