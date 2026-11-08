#pragma once
#include<cmath>
#include<ostream>

namespace AML
{
    struct vec2
    {
        float x, y;
  
      constexpr vec2() : x(0.0f), y(0.0f) {}
      constexpr vec2(float _x, float _y) 
         : x(_x), y(_y) {}

        // Compounding operators 
       vec2& operator+=(const vec2& other) {
           x += other.x; y += other.y;
           return *this;
       }
       vec2& operator-=(const vec2& other) {
           x -= other.x; y -= other.y;
           return *this;
       }
       vec2& operator*=(float scalar) {
           x *= scalar; y *= scalar; 
           return *this;
       }
       vec2& operator/=(float scalar) {
           x /= scalar; y /= scalar; 
           return *this;
       }
    };

    //basic operations
    inline vec2 operator+ (const vec2& lhs ,const vec2& rhs)
    {
        return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

     inline vec2 operator- (const vec2& lhs ,const vec2& rhs)
    {
        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

     inline vec2 operator* (float lhs ,const vec2& rhs)
    {
        return vec2(lhs * rhs.x, lhs * rhs.y);
    }

    inline vec2 operator* (const vec2& rhs, float lhs)
    {
        return vec2(lhs * rhs.x, lhs * rhs.y);
    }

     inline vec2 operator/ (const vec2& rhs, float lhs)
    {
        return vec2(rhs.x / lhs, rhs.y / lhs);
    }

    //vector utils
    inline std::ostream& operator<<(std::ostream& os, const vec2& me)
    {
        os << me.x << "i" <<", "<< me.y << "j";
        return os;
    }

    inline float dot(const vec2& lhs ,const vec2& rhs)
    {
        return (lhs.x * rhs.x + lhs.y * rhs.y);
    }

    inline float cross(const vec2& lhs ,const vec2& rhs)
    {
        return (lhs.x * rhs.y - lhs.y * rhs.x);   //area llgm
    }

    inline float length(const vec2& me)
    {
        return sqrt(me.x*me.x + me.y*me.y);
    }

    inline float length_sqr(const vec2& me)
    {
        return me.x*me.x + me.y*me.y;
    }

    inline vec2 normalize(const vec2 me) //unit vector
    {
        return vec2(me/length(me));
    }

    inline float distance(const vec2& head, const vec2& tail)
    {
        return length(tail - head);
    }    


    struct vec3
    {
       float x, y, z;
  
      constexpr vec3() : x(0.0f), y(0.0f), z(0.0f) {}
      constexpr vec3(float _x, float _y, float _z) 
         : x(_x), y(_y), z(_z) {}
      constexpr vec3(const vec2& v, float _z = 0.0f) //vector conversion casting
         : x(v.x), y(v.y), z(_z) {}

        // Compounding operators 
       vec3& operator+=(const vec3& other) {
           x += other.x; y += other.y; z += other.z;
           return *this;
       }
       vec3& operator-=(const vec3& other) {
           x -= other.x; y -= other.y; z -= other.z;
           return *this;
       }
       vec3& operator*=(float scalar) {
           x *= scalar; y *= scalar; z *= scalar;
           return *this;
       }
       vec3& operator/=(float scalar) {
           x /= scalar; y /= scalar; z /= scalar;
           return *this;
       }
    };

    //basic operations
    inline vec3 operator+ (const vec3& lhs ,const vec3& rhs)
    {
        return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

     inline vec3 operator- (const vec3& lhs ,const vec3& rhs)
    {
        return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

     inline vec3 operator* (float lhs ,const vec3& rhs)
    {
        return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

    inline vec3 operator* (const vec3& rhs, float lhs)
    {
        return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

     inline vec3 operator/ (const vec3& rhs, float lhs)
    {
        return vec3(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs);
    }

    //vector utils
    inline std::ostream& operator<<(std::ostream& os, const vec3& me)
    {
        os << me.x << "i" <<", "<< me.y << "j" <<", "<< me.z << "k";
        return os;
    }

    inline float dot(const vec3& lhs ,const vec3& rhs)
    {
        return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
    }

    inline vec3 cross(const vec3& lhs ,const vec3& rhs)
    {
        return vec3(lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x);
    }

    inline float length(const vec3& me)
    {
        return sqrt(me.x*me.x + me.y*me.y + me.z*me.z);
    }

    inline float length_sqr(const vec3& me)
    {
        return me.x*me.x + me.y*me.y + me.z*me.z;
    }

    inline vec3 normalize(const vec3& me) //unit vector
    {
        return vec3(me/length(me));
    }

    inline float distance(const vec3& head, const vec3& tail)
    {
        //return length(vec3(tail.x - head.x, tail.y - head.y, tail.z - head.z));
        return length(tail - head);
    }    


    struct vec4
    {
        // A union maps x,y,z,w to r,g,b,a in the exact same memory slots
        union {
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
            struct {};
            float data[4];
        };

        constexpr vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        constexpr vec4(float _x, float _y, float _z, float _w) 
          : x(_x), y(_y), z(_z), w(_w) {}
        vec4(const vec3& v, float _w = 1.0f)  //vector converion casting 
          : x(v.x), y(v.y), z(v.z), w(_w) {}

        inline vec4& operator+=(const vec4& other) {
            x += other.x; y += other.y; z += other.z; w += other.w;
            return *this;
        }
        inline vec4& operator-=(const vec4& other) {
            x -= other.x; y -= other.y; z -= other.z; w -= other.w;
            return *this;
        }
        inline vec4& operator*=(float scalar) {
            x *= scalar; y *= scalar; z *= scalar; w *= scalar;
            return *this;
        }
        inline vec4& operator/=(float scalar) {
            x /= scalar; y /= scalar; z /= scalar; w /= scalar;
            return *this;
        }
    };

    // Basic operators for vec4
    inline vec4 operator+(const vec4& lhs, const vec4& rhs) 
    {
        return vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    }
    inline vec4 operator-(const vec4& lhs, const vec4& rhs) 
    {
        return vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    }
    inline vec4 operator*(float lhs, const vec4& rhs) 
    {
        return vec4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
    }
    inline vec4 operator*(const vec4& rhs, float lhs) 
    {
        return vec4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
    }
    
    inline vec4 operator/(const vec4& rhs, float lhs) 
    {
        return vec4(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs, rhs.w / lhs);
    }

    // vec4 Utils
    inline std::ostream& operator<<(std::ostream& os, const vec4& me) 
    {
        os << me.x << "i, " << me.y << "j, " << me.z << "k, " << me.w << "w";
        return os;
    }
    inline float dot(const vec4& lhs, const vec4& rhs) 
    {
        return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w);
    }
    inline float length(const vec4& me) 
    {
        return sqrt(me.x*me.x + me.y*me.y + me.z*me.z + me.w*me.w);
    }
    inline float length_sqr(const vec4& me) 
    {
        return me.x*me.x + me.y*me.y + me.z*me.z + me.w*me.w;
    }
    inline vec4 normalize(const vec4& me) 
    {
        return me / length(me);
    }

    using color = vec4;

    // Component-wise vector multiplication for color
    inline vec4 operator*(const vec4& lhs, const vec4& rhs) 
    {
        return vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
    }

    // Color Utility Functions
    namespace colors 
    {
        // Predefined standard colors (RGBA)
        inline constexpr color black{0.0f, 0.0f, 0.0f, 1.0f};
        inline constexpr color white{1.0f, 1.0f, 1.0f, 1.0f};
        inline constexpr color red{1.0f, 0.0f, 0.0f, 1.0f};
        inline constexpr color green{0.0f, 1.0f, 0.0f, 1.0f};
        inline constexpr color blue{0.0f, 0.0f, 1.0f, 1.0f};
        inline constexpr color yellow{1.0f, 1.0f, 0.0f, 1.0f};
        inline constexpr color magenta{1.0f, 0.0f, 1.0f, 1.0f};
        inline constexpr color cyan{0.0f, 1.0f, 1.0f, 1.0f};
        inline constexpr color transparent{0.0f, 0.0f, 0.0f, 0.0f};

        // Clamps color channels between [0.0f, 1.0f]
        inline color clamp(const color& c) 
        {
            auto clamp_val = [](float val) {
                if (val < 0.0f) return 0.0f;
                if (val > 1.0f) return 1.0f;
                return val;
            };
            return color(clamp_val(c.r), clamp_val(c.g), clamp_val(c.b), clamp_val(c.a));
        }

        // Helper to convert float color [0.0f, 1.0f] to standard 8-bit integer channel [0, 255]
        // Useful when writing to PPM files, PNG files, or framebuffers
        inline int to_int255(float channel) 
        {
            if (channel < 0.0f) return 0;
            if (channel > 1.0f) return 255;
            return static_cast<int>(256.0f * channel); // 256 treats 1.0 correctly with scaling
        }
    }

    struct ray
    {
        vec3 origin, direction;

        ray() = default;
        ray(const vec3& _origin, const vec3& _direction) 
          : origin(_origin), direction(normalize(_direction)) {}

        vec3 at(float t) const
        {
            return origin + (direction*t);
        }

    };

    struct hit_record 
    {
        vec3 point;      
        vec3 normal;     
        float t = -1.0f; 
        bool front_face; 

        inline void set_face_normal(const ray& r, const vec3& outward_normal) 
        {
            front_face = dot(r.direction, outward_normal) < 0.0f;
            normal = front_face ? outward_normal : outward_normal * -1.0f;
        }
    };
}
