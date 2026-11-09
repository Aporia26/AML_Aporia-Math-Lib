#include "AML_Tests.hpp"
#include <sstream> 

// Include your custom library headers explicitly
#include "AML.hpp"

using namespace AML;

// Tight tolerance constraint for floating-point calculations
constexpr float EPSILON = 1e-5f;

// =========================================================================
// 1. MODULE: Math.hpp (SCALAR OPERATIONS)
// =========================================================================
AML_TEST(AML_Math, FactorialComprehensive) {
    // Edge case: Negative inputs must yield a failure code of -1
    AML_EXPECT_EQ(factorial(-100), -1);
    AML_EXPECT_EQ(factorial(-1), -1);

    // Boundary conditions
    AML_EXPECT_EQ(factorial(0), 1);
    AML_EXPECT_EQ(factorial(1), 1);

    // Standard progression values
    AML_EXPECT_EQ(factorial(2), 2);
    AML_EXPECT_EQ(factorial(3), 6);
    AML_EXPECT_EQ(factorial(4), 24);
    AML_EXPECT_EQ(factorial(5), 120);
}

AML_TEST(AML_Math, IsPrimeComprehensive) {
    // Edge cases: Negative numbers, zero, and unity are not primes
    AML_EXPECT_FALSE(isPrime(-11));
    AML_EXPECT_FALSE(isPrime(0));
    AML_EXPECT_FALSE(isPrime(1));

    // Boundary conditions: Smallest prime and composite values
    AML_EXPECT_TRUE(isPrime(2));
    AML_EXPECT_TRUE(isPrime(3));
    AML_EXPECT_FALSE(isPrime(4));

    // Generic structural primes vs composites
    AML_EXPECT_TRUE(isPrime(5));
    AML_EXPECT_FALSE(isPrime(9));
    AML_EXPECT_TRUE(isPrime(13));
    AML_EXPECT_FALSE(isPrime(15));
    AML_EXPECT_TRUE(isPrime(7919)); // Large known prime boundary entry
}

// =========================================================================
// 2. MODULE: Vector.hpp (VEC2, VEC3, VEC4, COLORS & RAY)
// =========================================================================
AML_TEST(AML_Vector, Vec2Exhaustive) {
    // Constructors
    vec2 default_v;
    AML_EXPECT_NEAR(default_v.x, 0.0f, EPSILON);
    AML_EXPECT_NEAR(default_v.y, 0.0f, EPSILON);

    vec2 explicit_v(3.0f, -4.0f);
    AML_EXPECT_NEAR(explicit_v.x, 3.0f, EPSILON);
    AML_EXPECT_NEAR(explicit_v.y, -4.0f, EPSILON);

    // Compounding Assignment Operators
    vec2 op_v(1.0f, 2.0f);
    op_v += vec2(2.0f, 3.0f);
    AML_EXPECT_NEAR(op_v.x, 3.0f, EPSILON);
    AML_EXPECT_NEAR(op_v.y, 5.0f, EPSILON);

    op_v -= vec2(1.0f, 1.0f);
    AML_EXPECT_NEAR(op_v.x, 2.0f, EPSILON);
    AML_EXPECT_NEAR(op_v.y, 4.0f, EPSILON);

    op_v *= 2.0f;
    AML_EXPECT_NEAR(op_v.x, 4.0f, EPSILON);
    AML_EXPECT_NEAR(op_v.y, 8.0f, EPSILON);

    op_v /= 4.0f;
    AML_EXPECT_NEAR(op_v.x, 1.0f, EPSILON);
    AML_EXPECT_NEAR(op_v.y, 2.0f, EPSILON);

    // Basic Binary Operators
    vec2 a(2.0f, 3.0f), b(4.0f, 5.0f);
    vec2 res_add = a + b;
    AML_EXPECT_NEAR(res_add.x, 6.0f, EPSILON);
    AML_EXPECT_NEAR(res_add.y, 8.0f, EPSILON);

    vec2 res_sub = a - b;
    AML_EXPECT_NEAR(res_sub.x, -2.0f, EPSILON);
    AML_EXPECT_NEAR(res_sub.y, -2.0f, EPSILON);

    vec2 res_mul1 = 2.0f * a;
    AML_EXPECT_NEAR(res_mul1.x, 4.0f, EPSILON);
    AML_EXPECT_NEAR(res_mul1.y, 6.0f, EPSILON);

    vec2 res_mul2 = a * 3.0f;
    AML_EXPECT_NEAR(res_mul2.x, 6.0f, EPSILON);
    AML_EXPECT_NEAR(res_mul2.y, 9.0f, EPSILON);

    vec2 res_div = b / 2.0f;
    AML_EXPECT_NEAR(res_div.x, 2.0f, EPSILON);
    AML_EXPECT_NEAR(res_div.y, 2.5f, EPSILON);

    // Math Utilities
    AML_EXPECT_NEAR(dot(a, b), 23.0f, EPSILON);       // (2*4) + (3*5)
    AML_EXPECT_NEAR(cross(a, b), -2.0f, EPSILON);     // (2*5) - (3*4)
    
    vec2 pythagorean(3.0f, 4.0f);
    AML_EXPECT_NEAR(length(pythagorean), 5.0f, EPSILON);
    AML_EXPECT_NEAR(length_sqr(pythagorean), 25.0f, EPSILON);

    vec2 norm = normalize(pythagorean);
    AML_EXPECT_NEAR(length(norm), 1.0f, EPSILON);
    AML_EXPECT_NEAR(norm.x, 0.6f, EPSILON);
    AML_EXPECT_NEAR(norm.y, 0.8f, EPSILON);

    AML_EXPECT_NEAR(distance(vec2(1,1), vec2(4,5)), 5.0f, EPSILON);

    // Ostream Serialization validation check
    std::stringstream ss;
    ss << pythagorean;
    AML_EXPECT_TRUE(ss.str() == "3i, 4j");
}

AML_TEST(AML_Vector, Vec3Exhaustive) {
    // Constructors & Castings
    vec3 default_v;
    AML_EXPECT_NEAR(default_v.z, 0.0f, EPSILON);

    vec3 explicit_v(1.0f, 2.0f, 3.0f);
    AML_EXPECT_NEAR(explicit_v.z, 3.0f, EPSILON);

    vec3 cast_v(vec2(5.0f, 6.0f), 7.0f);
    AML_EXPECT_NEAR(cast_v.x, 5.0f, EPSILON);
    AML_EXPECT_NEAR(cast_v.z, 7.0f, EPSILON);

    // Compounding Assignment Operators
    vec3 op_v(1.0f, 2.0f, 3.0f);
    op_v += vec3(1, 1, 1);   AML_EXPECT_NEAR(op_v.z, 4.0f, EPSILON);
    op_v -= vec3(1, 1, 1);   AML_EXPECT_NEAR(op_v.z, 3.0f, EPSILON);
    op_v *= 3.0f;            AML_EXPECT_NEAR(op_v.z, 9.0f, EPSILON);
    op_v /= 3.0f;            AML_EXPECT_NEAR(op_v.z, 3.0f, EPSILON);

    // Binary Operators
    vec3 a(1, 0, 0), b(0, 1, 0);
    vec3 res_add = a + b;    AML_EXPECT_NEAR(res_add.z, 0.0f, EPSILON);
    vec3 res_sub = a - b;    AML_EXPECT_NEAR(res_sub.y, -1.0f, EPSILON);
    vec3 res_mul1 = 2.0f * a;AML_EXPECT_NEAR(res_mul1.x, 2.0f, EPSILON);
    vec3 res_mul2 = a * 2.0f;AML_EXPECT_NEAR(res_mul2.x, 2.0f, EPSILON);
    vec3 res_div = a / 2.0f; AML_EXPECT_NEAR(res_div.x, 0.5f, EPSILON);

    // Utilities
    AML_EXPECT_NEAR(dot(vec3(1,2,3), vec3(4,5,6)), 32.0f, EPSILON);
    
    vec3 cross_res = cross(a, b); // i x j = k
    AML_EXPECT_NEAR(cross_res.x, 0.0f, EPSILON);
    AML_EXPECT_NEAR(cross_res.y, 0.0f, EPSILON);
    AML_EXPECT_NEAR(cross_res.z, 1.0f, EPSILON);

    vec3 len_v(1, 2, 2);
    AML_EXPECT_NEAR(length(len_v), 3.0f, EPSILON);
    AML_EXPECT_NEAR(length_sqr(len_v), 9.0f, EPSILON);
    AML_EXPECT_NEAR(length(normalize(len_v)), 1.0f, EPSILON);
    AML_EXPECT_NEAR(distance(vec3(0,0,0), vec3(1,2,2)), 3.0f, EPSILON);

    std::stringstream ss;
    ss << len_v;
    AML_EXPECT_TRUE(ss.str() == "1i, 2j, 2k");
}

AML_TEST(AML_Vector, Vec4AndColorExhaustive) {
    // Union mapping structure verification (x,y,z,w vs r,g,b,a alignment verification)
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    AML_EXPECT_NEAR(v.x, v.r, EPSILON);
    AML_EXPECT_NEAR(v.y, v.g, EPSILON);
    AML_EXPECT_NEAR(v.z, v.b, EPSILON);
    AML_EXPECT_NEAR(v.w, v.a, EPSILON);

    // Assignment & Binary check operations
    vec4 op_v(1,1,1,1);
    op_v += vec4(1,1,1,1); AML_EXPECT_NEAR(op_v.w, 2.0f, EPSILON);
    op_v -= vec4(1,1,1,1); AML_EXPECT_NEAR(op_v.w, 1.0f, EPSILON);
    op_v *= 4.0f;          AML_EXPECT_NEAR(op_v.w, 4.0f, EPSILON);
    op_v /= 2.0f;          AML_EXPECT_NEAR(op_v.w, 2.0f, EPSILON);

    vec4 a(1,2,3,4), b(2,3,4,5);
    AML_EXPECT_NEAR((a+b).w, 9.0f, EPSILON);
    AML_EXPECT_NEAR((a-b).w, -1.0f, EPSILON);
    AML_EXPECT_NEAR((2.0f*a).w, 8.0f, EPSILON);
    AML_EXPECT_NEAR((a*2.0f).w, 8.0f, EPSILON);
    AML_EXPECT_NEAR((a/2.0f).w, 2.0f, EPSILON);

    // Serialization & Math utils
    std::stringstream ss;
    ss << a;
    AML_EXPECT_TRUE(ss.str() == "1i, 2j, 3k, 4w");
    AML_EXPECT_NEAR(dot(a, b), 40.0f, EPSILON);
    AML_EXPECT_NEAR(length_sqr(vec4(1,1,1,1)), 4.0f, EPSILON);
    AML_EXPECT_NEAR(length(normalize(a)), 1.0f, EPSILON);

    // Color element-wise modulation operator check (Component-wise multiplier)
    color c1(0.5f, 0.5f, 0.5f, 1.0f);
    color c2(2.0f, 0.0f, 1.0f, 1.0f);
    color modulated = c1 * c2;
    AML_EXPECT_NEAR(modulated.r, 1.0f, EPSILON);
    AML_EXPECT_NEAR(modulated.g, 0.0f, EPSILON);
    AML_EXPECT_NEAR(modulated.b, 0.5f, EPSILON);

    // Static Palette Presets mapping validation
    AML_EXPECT_NEAR(colors::black.r, 0.0f, EPSILON);
    AML_EXPECT_NEAR(colors::white.g, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::red.r, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::green.g, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::blue.b, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::yellow.r, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::magenta.b, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::cyan.g, 1.0f, EPSILON);
    AML_EXPECT_NEAR(colors::transparent.a, 0.0f, EPSILON);

    // Conversion thresholds
    AML_EXPECT_EQ(colors::to_int255(1.0f), 256); 
    AML_EXPECT_EQ(colors::to_int255(-1.0f), 0);
    AML_EXPECT_EQ(colors::to_int255(0.5f), 128);
}

AML_TEST(AML_Vector, RayExhaustive) {
    vec3 origin(1, 2, 3);
    vec3 direction(0, 2, 0); // Non-normalized input check
    ray r(origin, direction);

    // Ray construction maps auto-normalized unit configurations
    AML_EXPECT_NEAR(r.direction.y, 1.0f, EPSILON);
    AML_EXPECT_NEAR(r.direction.x, 0.0f, EPSILON);

    // Ray evaluation parameter extrapolation t tests
    vec3 tracking_point = r.at(5.0f);
    AML_EXPECT_NEAR(tracking_point.x, 1.0f, EPSILON);
    AML_EXPECT_NEAR(tracking_point.y, 7.0f, EPSILON); // 2 + (1.0 * 5)
    AML_EXPECT_NEAR(tracking_point.z, 3.0f, EPSILON);
}

// =========================================================================
// 3. MODULE: Matrix.hpp (MAT3, MAT4, PROJECTIONS & LOOKAT)
// =========================================================================
AML_TEST(AML_Matrix, Mat3Exhaustive) {
    // Identity Default setup matching configuration
    mat3 i;
    AML_EXPECT_NEAR(i[0].x, 1.0f, EPSILON);
    AML_EXPECT_NEAR(i[1].y, 1.0f, EPSILON);
    AML_EXPECT_NEAR(i[2].z, 1.0f, EPSILON);
    AML_EXPECT_NEAR(i[0].y, 0.0f, EPSILON);

    // Multi-operator transformations check
    mat3 m1(vec3(1,2,3), vec3(4,5,6), vec3(7,8,9));
    mat3 m2(vec3(1,1,1), vec3(1,1,1), vec3(1,1,1));

    mat3 res_add = m1 + m2; AML_EXPECT_NEAR(res_add[0].x, 2.0f, EPSILON);
    mat3 res_sub = m1 - m2; AML_EXPECT_NEAR(res_sub[2].z, 8.0f, EPSILON);
    
    // Scale variants verification mapping checks
    mat3 res_scale1 = m1 * 2.0f; AML_EXPECT_NEAR(res_scale1[1].y, 10.0f, EPSILON);
    mat3 res_scale2 = 2.0f * m1; AML_EXPECT_NEAR(res_scale2[1].y, 10.0f, EPSILON);
    mat3 res_scale3 = m1 * 2.0f; AML_EXPECT_NEAR(res_scale3[1].y, 10.0f, EPSILON); // Covers overloaded 3rd scale signature

    // Transform vector checks (Column major operation layout)
    vec3 transformed_v = m1 * vec3(1, 1, 1);
    AML_EXPECT_NEAR(transformed_v.x, 12.0f, EPSILON); // 11 + 41 + 7*1
// Matrix cross multiplication tracking bounds configuration
mat3 mul_mat = i * m1;
AML_EXPECT_NEAR(mul_mat[1].y, 5.0f, EPSILON);
// Transpose
mat3 t_mat = transpose(m1);
AML_EXPECT_NEAR(t_mat[1].x, 2.0f, EPSILON); // row 1 col 0 swaps down to col 1 row 0
// Determinant and Singularity fallback boundaries
mat3 singular(vec3(1,2,3), vec3(2,4,6), vec3(0,0,0)); // Linear combination layout dependency
AML_EXPECT_NEAR(det(singular), 0.0f, EPSILON);
mat3 fallback_inv = inverse(singular);
AML_EXPECT_NEAR(fallback_inv[0].x, 1.0f, EPSILON); // Resets back safely to identity baseline
}
AML_TEST(AML_Matrix, Mat4AndTransformsExhaustive) {
// Structural layout validation check
mat4 identity;
AML_EXPECT_NEAR(identity[3].w, 1.0f, EPSILON);
AML_EXPECT_NEAR(identity[0].w, 0.0f, EPSILON);
mat4 m1(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(2,3,4,1));
mat4 m2 = identity + identity; AML_EXPECT_NEAR(m2[0].x, 2.0f, EPSILON);
mat4 m3 = m2 - identity;       AML_EXPECT_NEAR(m3[0].x, 1.0f, EPSILON);
mat4 m4 = identity * 3.0f;     AML_EXPECT_NEAR(m4[0].x, 3.0f, EPSILON);
mat4 m5 = 3.0f * identity;     AML_EXPECT_NEAR(m5[0].x, 3.0f, EPSILON);
// Vector Multiplier mapping layout
vec4 t_vec = m1 * vec4(0, 0, 0, 1);
AML_EXPECT_NEAR(t_vec.x, 2.0f, EPSILON);
// Matrix cross matrix product bounds tracking loop configurations
mat4 double_mat = identity * identity;
AML_EXPECT_NEAR(double_mat[2].z, 1.0f, EPSILON);
// Transpose
mat4 base_t(vec4(1,2,3,4), vec4(5,6,7,8), vec4(9,10,11,12), vec4(13,14,15,16));
mat4 inv_t = transpose(base_t);
AML_EXPECT_NEAR(inv_t[1].x, 2.0f, EPSILON);
// Geometric Transform Generators
mat4 t1 = translate(5.0f, -2.0f, 4.0f);
AML_EXPECT_NEAR(t1[3].x, 5.0f, EPSILON);
AML_EXPECT_NEAR(t1[3].y, -2.0f, EPSILON);
mat4 t2 = translate(vec3(1, 2, 3));
AML_EXPECT_NEAR(t2[3].z, 3.0f, EPSILON);
mat4 s1 = scale(2.0f, 0.5f, 4.0f);
AML_EXPECT_NEAR(s1[0].x, 2.0f, EPSILON);
AML_EXPECT_NEAR(s1[1].y, 0.5f, EPSILON);
mat4 s2 = scale(vec3(3,3,3));
AML_EXPECT_NEAR(s2[2].z, 3.0f, EPSILON);
// Rotations around structural layout pivots
mat4 rotX = rotateX(0.0f); AML_EXPECT_NEAR(rotX[1].y, 1.0f, EPSILON);
mat4 rotY = rotateY(0.0f); AML_EXPECT_NEAR(rotY[0].x, 1.0f, EPSILON);
mat4 rotZ = rotateZ(0.0f); AML_EXPECT_NEAR(rotZ[0].x, 1.0f, EPSILON);
// Projections matrices pipeline output checks
mat4 pers = perspective(0.785398f, 1.333f, 0.1f, 100.0f);
AML_EXPECT_NEAR(pers[2].w, -1.0f, EPSILON); // Asserts depth parameter caching component tracking inside perspective projection configuration structures
mat4 orthographic = ortho(-1, 1, -1, 1, 0.1f, 100.0f);
AML_EXPECT_NEAR(orthographic[3].w, 1.0f, EPSILON);
}
// =========================================================================
// 4. MODULE: Geometry.hpp & Intersection.hpp (PRIMITIVES & OVERLAPS)
// =========================================================================
AML_TEST(AML_Geometry, PrimitiveConstructors) {
// Circle configurations
circle c_def;
AML_EXPECT_NEAR(c_def.radius, 1.0f, EPSILON);
circle c_exp(vec2(1,2), 5.0f);
AML_EXPECT_NEAR(c_exp.radius, 5.0f, EPSILON);
// AABB bounds layouts
AABB2D box_def;
AML_EXPECT_NEAR(box_def.min_pt.x, 0.0f, EPSILON);
AABB2D box_exp(vec2(-1,-1), vec2(1,1));
AML_EXPECT_NEAR(box_exp.max_pt.y, 1.0f, EPSILON);
// OBB orientation definitions
OBB2D obb_def;
AML_EXPECT_NEAR(obb_def.extents.x, 0.5f, EPSILON);
OBB2D obb_exp(vec2(0,0), vec2(10,5), 1.57f);
AML_EXPECT_NEAR(obb_exp.angleRadians, 1.57f, EPSILON);
// Plane orientations normalization mapping checks
plane p_def;
AML_EXPECT_NEAR(p_def.normal.y, 1.0f, EPSILON);
plane p_exp(vec3(0, 10, 0), 5.0f); // Should downscale normal scale values uniformly to 1.0 unit sizing
AML_EXPECT_NEAR(p_exp.normal.y, 1.0f, EPSILON);
// Sphere dimensions
sphere s_def;
AML_EXPECT_NEAR(s_def.radius, 1.0f, EPSILON);
sphere s_exp(vec3(1,2,3), 4.5f);
AML_EXPECT_NEAR(s_exp.radius, 4.5f, EPSILON);
}
AML_TEST(AML_Intersection, ComprehensiveOverlapTests) {
// 1. Circle vs Circle Overlaps
circle c1(vec2(0, 0), 1.0f);
circle c2(vec2(1.5f, 0), 1.0f); // Overlapping
circle c3(vec2(2.5f, 0), 1.0f); // Separated boundary
AML_EXPECT_TRUE(overlap_circle(c1, c2));
AML_EXPECT_FALSE(overlap_circle(c1, c3));
// 2. AABB vs AABB Overlaps
AABB2D aabb1(vec2(0,0), vec2(2,2));
AABB2D aabb2(vec2(1,1), vec2(3,3)); // Intersecting
AABB2D aabb3(vec2(3,3), vec2(5,5)); // Edge touch or separated boundary configuration
AML_EXPECT_TRUE(overlap_aabb2d(aabb1, aabb2));
AML_EXPECT_FALSE(overlap_aabb2d(aabb1, aabb3));
// 3. Circle vs AABB2D Overlaps
circle cc(vec2(2.5f, 1.0f), 1.0f);
AABB2D box(vec2(0,0), vec2(2,2)); // Distance from center 2.5 to box boundary edge 2.0 is 0.5 <= radius 1.0
AML_EXPECT_TRUE(overlap_circle_vs_aabb(cc, box));
circle cc_far(vec2(4.0f, 1.0f), 1.0f);
AML_EXPECT_FALSE(overlap_circle_vs_aabb(cc_far, box));
// 4. OBB vs OBB Separating Axis Theorem (SAT Verification)
OBB2D obb1(vec2(0,0), vec2(1,1), 0.0f);
OBB2D obb2(vec2(1.8f, 0), vec2(1,1), 0.0f); // Colliding layout overlay
OBB2D obb3(vec2(3.0f, 0), vec2(1,1), 0.0f); // Distinct separation
AML_EXPECT_TRUE(overlap_obb2d(obb1, obb2));
AML_EXPECT_FALSE(overlap_obb2d(obb1, obb3));
// 5. 3D Sphere vs Sphere
vec3 sA(0,0,0), sB(0,0,1.5f), sC(0,0,5.0f);
AML_EXPECT_TRUE(sphere_vs_sphere(sA, 1.0f, sB, 1.0f));
AML_EXPECT_FALSE(sphere_vs_sphere(sA, 1.0f, sC, 1.0f));
}
// =========================================================================
// RUNNER SYSTEM INITIALIZATION ENTRY POINT
// =========================================================================
int main() {
return AML_Test::RunAllTests();
}
