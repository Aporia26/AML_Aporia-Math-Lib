#pragma once;  //reads this only once 

struct vec3 {

    float x;
    float y;
    float z;
};

vec3 add(vec3 &A, vec3 &B);
vec3 subst(vec3 &A, vec3 &B);
float dot(vec3 &A, vec3 &B);
vec3 cross(vec3 &A, vec3 &B);
float magnitude(vec3 A);
vec3 unit_vector(vec3 A);
vec3 scale(vec3 A, float scalar);