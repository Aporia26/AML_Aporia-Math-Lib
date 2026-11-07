#include<iostream>
#include<cmath>
#include "Vector.h"

//struct vec3 {
//
//    float x;
//    float y;
//    float z;
//};

//vec3 add(vec3 &A, vec3 &B);
//vec3 subst(vec3 &A, vec3 &B);
//float dot(vec3 &A, vec3 &B);
//vec3 cross(vec3 &A, vec3 &B);
//float magnitude(vec3 A);
//vec3 unit_vector(vec3 A);
//vec3 scale(vec3 A, float scalar);

int main(){
    vec3 A = {2, 3, 4};
    vec3 B = {5, 0, 11};

vec3 C = add(A,B);
float D = dot(A,B);
vec3 E = cross(A,B);
float Ab = magnitude(A);
vec3 F = unit_vector(B);

std::cout << C.x <<" "<< C.y <<" "<< C.z << '\n';
std::cout << D << '\n';
std::cout << E.x <<" "<< E.y <<" "<< E.z << '\n';
std::cout << Ab << '\n';
std::cout << F.x<<" "<<F.y<<" "<<F.z <<'\n';

float scalar = 6;
vec3 G = scale(A,scalar);
std::cout << G.x <<" "<< G.y <<" "<< G.z << '\n';

    return 0;
}
vec3 add(vec3 &A, vec3 &B){
 
    vec3 result = {A.x + B.x, A.y + B.y, A.z + B.z};
    return result;
}
vec3 subst(vec3 &A, vec3 &B){
    vec3 result = {A.x-B.x,A.y-B.y,A.z-B.z};
    return result;
}
float dot(vec3 &A, vec3 &B){
    float result = A.x*B.x + A.y*B.y + A.z*B.z;
    return result;

}
vec3 cross( vec3 &A, vec3 &B){
    vec3 result = {A.y*B.z - A.z*B.y, -(A.x*B.z - A.z*B.x), A.x*B.y - A.y*B.x};
    return result;
}
float magnitude(vec3 A){
    float result = sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
    return result;
}
vec3 unit_vector(vec3 A){
    vec3 result = {//A.x/sqrt(A.x*A.x + A.y*A.y + A.z*A.z),
                    A.x/magnitude(A),
                     A.y/magnitude(A),
                     A.z/magnitude(A)};
    return result;
}
vec3 scale(vec3 A,float scalar){
    vec3 result = {scalar*A.x, scalar*A.y, scalar*A.z};
    return result;
}