#include<iostream>
#include<cmath>
#include "Matrices.h"



int main(){



    return 0;
}
mat4x4 add(mat4x4 A, mat4x4 B){
    mat4x4 result = {A.element[0]+B.element[0], A.element[1]+B.element[1], A.element[2]+B.element[2],
                     A.element[3]+B.element[3], A.element[4]+B.element[4], A.element[5]+B.element[5],
                     A.element[8]+B.element[8], A.element[9]+B.element[9], A.element[10]+B.element[10],
                     A.element[13]+B.element[13], A.element[14]+B.element[14], A.element[15]+B.element[15],
                     };
     return result;                

}
mat4x4 subst(mat4x4 A, mat4x4 B){
       mat4x4 result = {A.element[0]-B.element[0], A.element[1]-B.element[1], A.element[2]-B.element[2],
                     A.element[3]-B.element[3], A.element[4]-B.element[4], A.element[5]-B.element[5],
                     A.element[8]-B.element[8], A.element[9]-B.element[9], A.element[10]-B.element[10],
                     A.element[13]-B.element[13], A.element[14]-B.element[14], A.element[15]-B.element[15],
                     };
     return result; 

}
float det(mat4x4 A){

    float value = 
        A.element[0] * (A.element[5] * (A.element[10] * A.element[15] - A.element[11] * A.element[14]) - A.element[6] * (A.element[9] * A.element[15] - A.element[11] * A.element[13]) + A.element[7] * (A.element[9] * A.element[14] - A.element[10] * A.element[13])) -
        A.element[1] * (A.element[4] * (A.element[10] * A.element[15] - A.element[11] * A.element[14]) - A.element[6] * (A.element[8] * A.element[15] - A.element[11] * A.element[12]) + A.element[7] * (A.element[8] * A.element[14] - A.element[10] * A.element[12])) +
        A.element[2] * (A.element[4] * (A.element[9] * A.element[15] - A.element[11] * A.element[13]) - A.element[5] * (A.element[8] * A.element[15] - A.element[11] * A.element[12]) + A.element[7] * (A.element[8] * A.element[13] - A.element[9] * A.element[12])) -
        A.element[3] * (A.element[4] * (A.element[9] * A.element[14] - A.element[10] * A.element[13]) - A.element[5] * (A.element[8] * A.element[14] - A.element[10] * A.element[12]) + A.element[6] * (A.element[8] * A.element[13] - A.element[9] * A.element[12]));

    return value;
}
mat4x4 scale(mat4x4 A, float scalar){
    mat4x4 result = {A.element[0]*scalar, A.element[1]*scalar, A.element[2]*scalar,
                     A.element[3]*scalar, A.element[4]*scalar, A.element[5]*scalar,
                     A.element[8]*scalar, A.element[9]*scalar, A.element[10]*scalar,
                     A.element[13]*scalar, A.element[14]*scalar, A.element[15]*scalar,
                     };
    return result;
}
// mat4x4 product(mat4x4 A, mat4x4 B){
//     mat4x4 result = {1,0,0,0,
//                      0,1,0,0,
//                      0,0,1,0,
//                      0,0,0,0};
//     return result;
// }


mat3x3 add(mat3x3 A, mat3x3 B){
     mat3x3 result = {A.element[0]+B.element[0], A.element[1]+B.element[1], A.element[2]+B.element[2],
                     A.element[3]+B.element[3], A.element[4]+B.element[4], A.element[5]+B.element[5],
                     A.element[6]+B.element[6], A.element[7]+B.element[7], A.element[8]+B.element[8],
                     };
     return result; 
}
mat3x3 subst(mat3x3 A, mat3x3 B){
    mat3x3 result = {A.element[0]-B.element[0], A.element[1]-B.element[1], A.element[2]-B.element[2],
                     A.element[3]-B.element[3], A.element[4]-B.element[4], A.element[5]-B.element[5],
                     A.element[6]-B.element[6], A.element[7]-B.element[7], A.element[8]-B.element[8],
                     };
     return result; 
}
float det(mat3x3 A){
    float result = A.element[0]*(A.element[4]*A.element[8] - A.element[5]*A.element[7]) 
                   - A.element[1]*(A.element[3]*A.element[8] - A.element[6]*A.element[5])
                   + A.element[2]*(A.element[3]*A.element[7] - A.element[4]*A.element[6]);
    return result;
}
mat3x3 scale(mat3x3 A, float scalar){
    mat3x3 result = {A.element[0]*scalar, A.element[1]*scalar, A.element[2]*scalar,
                     A.element[3]*scalar, A.element[4]*scalar, A.element[5]*scalar,
                     A.element[6]*scalar, A.element[7]*scalar, A.element[8]*scalar,
                     };
    return result;
}
mat3x3 product(mat3x3 A, mat3x3 B){
    mat3x3 result;
   //row x column
    result.element[0] = A.element[0]*B.element[0] + A.element[1]*B.element[3] + A.element[2]*B.element[6];
    result.element[1] = A.element[0]*B.element[1] + A.element[1]*B.element[4] + A.element[2]*B.element[7];
    result.element[2] = A.element[0]*B.element[2] + A.element[1]*B.element[5] + A.element[2]*B.element[8];

    result.element[3] = A.element[3]*B.element[0] + A.element[4]*B.element[3] + A.element[5]*B.element[6];
    result.element[4] = A.element[3]*B.element[1] + A.element[4]*B.element[4] + A.element[5]*B.element[7];
    result.element[5] = A.element[3]*B.element[2] + A.element[4]*B.element[5] + A.element[5]*B.element[8];

    result.element[6] = A.element[6]*B.element[0] + A.element[7]*B.element[3] + A.element[8]*B.element[6];
    result.element[7] = A.element[6]*B.element[1] + A.element[7]*B.element[4] + A.element[8]*B.element[7];
    result.element[8] = A.element[6]*B.element[2] + A.element[7]*B.element[5] + A.element[8]*B.element[8];

    return result;

}