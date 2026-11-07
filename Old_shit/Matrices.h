#pragma once;

struct mat4x4 {

    float element[16];
};

struct mat3x3{
    float element[9];
};

mat4x4 add(mat4x4 A, mat4x4 B);
mat4x4 subst(mat4x4 A, mat4x4 B);
float det(mat4x4 A);
mat4x4 scale(mat4x4 A, float scalar);
mat4x4 product(mat4x4 A, mat4x4 B);

mat3x3 add(mat3x3 A, mat3x3 B);
mat3x3 subst(mat3x3 A, mat3x3 B);
float det(mat3x3 A);
mat3x3 scale(mat3x3 A, float scalar);
mat3x3 product(mat3x3 A, mat3x3 B);